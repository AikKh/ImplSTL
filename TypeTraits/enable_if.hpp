#pragma once

namespace atl
{
	template<bool value, typename T = void>
	struct EnableIf;

	template<typename T>
	struct EnableIf<true, T> {
		using Type = T;
	};
}