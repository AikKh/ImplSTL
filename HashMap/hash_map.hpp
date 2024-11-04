#pragma once

#include <forward_list>
#include <vector>
#include <utility>
#include <type_traits>

#include "hash.hpp"
#include "node.hpp"
#include "iterator.hpp"
#include "../Allocators/default_allocator.hpp"

namespace atl
{

	template<typename Key, typename T, template<typename> class hash = Hash, template<typename> class Allocator = DefaultAllocator>
	class HashMap {
	public:
		using key_type = Key;
		using value_type = T;
		using hash_func = hash<Key>;
		using pair_type = std::pair<const Key, T>;
		using node = Node<pair_type>;
		using allocator_type = Allocator<node*>;

		static constexpr double MaxLoadFactor = 0.7;

		HashMap() : m_data{ nullptr }, m_size{ 0 }, m_capacity{ 0 }
		{

		}

		void Insert(pair_type pair)
		{
			if (LoadFactor() > MaxLoadFactor)
			{
				Rehash(m_capacity > 0 ? m_capacity * 2 : 1);
			}

			PushPair(std::move(pair), m_data, m_capacity);
			m_size++;
		}

		void Delete(const key_type& key)
		{
			auto index = GetIndex(key, m_capacity);
			node* n = m_data[index];

			if (!n) return;

			if (n->value.first == key)
			{
				auto tmp = n->next;
				delete n;
				m_data[index] = tmp;
				return;
			}

			while (n->next)
			{
				if (n->next->value.first == key)
				{
					auto tmp = n->next->next;
					delete n->next;
					n->next = tmp;
					return;
				}

				n = n->next;
			}
		}

		value_type* Search(const key_type& key)
		{
			auto index = GetIndex(key, m_capacity);

			node* n = m_data[index];

			while (n)
			{
				if (n->value.first == key)
				{
					return &n->value.second;
				}

				n = n->next;
			}

			return nullptr;
		}

		void Log() const
		{
			std::cout << "HashMap Log:\n";
			std::cout << "Capacity: " << m_capacity << "\n";
			std::cout << "Size: " << m_size << "\n";
			std::cout << "Load Factor: " << LoadFactor() << "\n";

			// Iterate over each bucket and display its contents
			for (size_t i = 0; i < m_capacity; ++i)
			{
				std::cout << "Bucket " << i << ": ";
				node* current = m_data[i];
				if (!current)
				{
					std::cout << "Empty";
				}
				else
				{
					while (current)
					{
						std::cout << "{ " << current->value.first << " : " << current->value.second << " } ";
						current = current->next;
						if (current)
						{
							std::cout << "-> ";
						}
					}
				}
				std::cout << "\n";
			}
			std::cout << std::endl;
		}

		Iterator<key_type, value_type> begin() const
		{
			return Iterator<key_type, value_type>{ m_data, m_capacity };
		}

		Iterator<key_type, value_type> end() const
		{
			return Iterator<key_type, value_type>{ nullptr, 0 };
		}

	private:
		void Rehash(size_t new_size)
		{
			if (new_size <= m_size)
				return;

			allocator_type alloc{};


			node** new_data = alloc.allocate(new_size);

			for (auto it = this->begin(); it != this->end(); ++it)
			{
				auto& pair = *it;
				PushPair(std::move(pair), new_data, new_size);
			}

			alloc.deallocate(m_data, m_capacity);
			m_capacity = new_size;
			m_data = new_data;
		}

		double LoadFactor() const
		{
			//return static_cast<double>(m_size + 1) / static_cast<double>(m_capacity);
			return m_capacity > 0 ? static_cast<double>(m_size) / static_cast<double>(m_capacity) : 1.0;
		}

		void PushPair(pair_type pair, node** dest, size_t size)
		{
			auto index = GetIndex(pair.first, size);

			node* tmp = dest[index];
			dest[index] = new node{std::move(pair), tmp};
		}

		inline size_t GetIndex(const key_type& key, size_t size)
		{
			return m_hfunc(key) % size;
		}

	private:
		node** m_data;
		int m_size;
		int m_capacity;

		hash_func m_hfunc;
	};

}
