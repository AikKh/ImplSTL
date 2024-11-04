#pragma once

#include <type_traits>

namespace atl
{

template<typename T>
T&& forward(std::remove_reference_t<T> const& arg)
{
	return static_cast<T&&>(arg);
}

template<typename T>
T&& forward(std::remove_reference_t<T> const&& arg)
{
	return static_cast<T&&>(arg);
}

}
