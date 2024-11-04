#pragma once

#include "integral_constant.hpp"
#include "void_t.hpp"

namespace atl
{

template<typename T, typename = void>
struct IsDefaultConstructible : FalseType {};

template<typename T>
struct IsDefaultConstructible<T, VoidT<decltype(T{}) >> : TrueType {};

}
