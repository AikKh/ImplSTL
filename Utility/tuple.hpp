#pragma once

#include "../TypeTraits/forward.hpp"

namespace atl
{

template<typename Head, typename... Tail>
struct Tuple {
public:
	Tuple(const Head& head, const Tuple<Tail...>& tail) : m_head{ head }, m_tail { tail } {}

	template<typename VHead, typename ...VTail>
	Tuple(VHead&& head, VTail&&... tail): m_head{ forward(head) }, m_tail{ forward(tail)... } {}

private:
	Head m_head;
	Tuple<Tail...> m_tail;
};

template<>
struct Tuple<> {};

}
