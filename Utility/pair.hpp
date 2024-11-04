#pragma once

namespace atl
{

template<typename T1, typename T2>
struct Pair {
	T1 first;
	T2 second;

	bool operator==(const Pair& other) const
	{
		return first == other.first && second == other.second;
	}
};

}
