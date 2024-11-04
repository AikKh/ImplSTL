#pragma once

#include <iostream>

using namespace std;

namespace atl::hash
{
	int bad(int x)
	{
		cout << "Bad" << endl;
		return x;
	}

	int good(int x)
	{
		cout << "Good" << endl;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x;
	}

	int very_good(int x)
	{
		cout << "Veery" << endl;
		constexpr int c2 = 0x27d4eb2d;
		x = (x ^ 61) ^ (x >> 16);
		x = x + (x << 3);
		x = x ^ (x >> 4);
		x = x * c2;
		x = x ^ (x >> 15);
		return x;

	}
}