#pragma once

#include "HashFunctions/int_hash.hpp"
#include "hash_selector.hpp"

namespace atl
{
	template<typename T>
	struct Hash;

	template<>
	struct Hash<int> {
	public:
		using Func = RandomSelector<int, int>::Selector<hash::bad, hash::good, hash::very_good>;
		
		size_t operator()(int x) const
		{
			return Func::Call(x);
		}
	};
}