#pragma once

#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
#include <stdexcept>

#include "../Allocators/default_allocator.hpp"
#include "iterator.hpp"

namespace atl
{

template<typename T, template<typename> class Allocator = DefaultAllocator>
class Vector {
public:
	static_assert(std::is_same_v<std::remove_const_t<T>, T>, "Your type can't be const");

	using value_type = T;
	using allocator_type = Allocator<T>;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;

	Vector() : m_data{ nullptr }, m_size{ 0 }, m_capacity{ 0 } {}

	Vector(size_type reserved) : Vector()
	{
		Reserve(reserved);
	}

	Vector(std::initializer_list<T> values) : Vector(values.size())
	{	
		m_size = values.size();
		
		// initializer_list elements can't be moved, so nothing moves here
		std::move(values.begin(), values.end(), m_data);
	}

	// Chapter 6.4
	Vector(const volatile Vector<T>&) = delete;

	template<typename U>
	Vector(const Vector<U>& other)
	{
		Reserve(other.m_size);
		for (auto&& i : other)
		{
			Push(i);
		}
	}

	// Chapter 6.4
	Vector(volatile Vector<T>&&) = delete;

	template<typename U>
	Vector(Vector<U>&& other)
	{
		Reserve(other.m_size);
		for (auto&& i : other)
		{
			Push(std::move(i));
		}

		other.Clear();
	}

	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	void Push(U&& value)
	{
		if (m_size >= m_capacity)
		{
			Reserve(m_capacity > 0 ? m_capacity * 2 : 1);
		}
		m_data[m_size++] = std::forward<U>(value);
	}

	T Pop()
	{
		return std::move(m_data[--m_size]);
	}

	void Log() const
	{
		std::cout << "---------------------------------\n";
		std::cout << "Vector State:" << std::endl;
		std::cout << "Size: " << m_size << std::endl;
		std::cout << "Capacity: " << m_capacity << std::endl;
		std::cout << "Elements: ";
		for (size_type i = 0; i < m_size; ++i)
		{
			std::cout << m_data[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "---------------------------------\n";
	}

	bool Empty() const
	{
		return m_size == 0;
	}

	void Clear()
	{
		m_size = 0;
	}

	size_type Capacity() const
	{
		return m_capacity;
	}

	size_type Size() const
	{
		return m_size;
	}

	const T& Back() const
	{
		return m_data[m_size - 1];
	}

	T& At(size_type index)
	{
		if (0 > index || index >= m_size)
			throw std::out_of_range("Index out of range");
		return m_data[index];
	}

	const T& At(size_type index) const
	{
		if (0 > index || index >= m_size)
			throw std::out_of_range("Index out of range");
		return m_data[index];
	}

	T& operator[](size_type index)
	{
		return m_data[index];
	}

	const T& operator[](size_type index) const
	{
		return m_data[index];
	}

	// Chapter 6.4
	Vector<T>& operator=(const volatile Vector<T>&) = delete;

	template<typename U>
	Vector<T>& operator=(const Vector<U>& other)
	{
		if (this == reinterpret_cast<const Vector<T>*>(&other))
		{
			return *this;
		}

		Clear();
		Reserve(other.m_capacity);

		for (auto&& i : other)
		{
			Push(i);
		}

		return *this;
	}

	Vector<T>& operator=(volatile Vector<T>&& other) = delete;

	template<typename U>
	Vector<T>& operator=(Vector<U>&& other)
	{
		if (this == reinterpret_cast<const Vector<T>*>(&other))
		{
			return *this;
		}

		Clear();
		Reserve(other.m_capacity);

		for (auto&& i : other)
		{
			Push(std::move(i));
		}

		other.Clear();

		return *this;
	}

	Iterator<T> begin()
	{
		return Iterator<T>{ m_data };
	}

	Iterator<T> end()
	{
		return Iterator<T>{ m_data + m_size };
	}

	~Vector()
	{
		m_allocator.deallocate(m_data, m_capacity);
	}

	template<typename, template<typename> class> friend class Vector;

	void Reserve(size_type new_size)
	{
		if (new_size <= m_size)
			return;

		T* new_data = m_allocator.allocate(new_size);

		for (int i = 0; i < m_size; i++)
		{
			new_data[i] = std::move(m_data[i]);
		}

		m_allocator.deallocate(m_data, m_capacity);

		m_data = new_data;
		m_capacity = new_size;
	}

private:
	pointer m_data;
	size_type m_size;
	size_type m_capacity;

	allocator_type m_allocator;
};

}
