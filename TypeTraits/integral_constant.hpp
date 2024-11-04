#pragma once

namespace atl
{

template<typename T, T val>
struct IntegralConstant 
{
    static constexpr T value = v;
    using value_type = T;
};

using TrueType = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;

}