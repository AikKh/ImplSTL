#pragma once

namespace atl
{
	template<typename Iterator>
	struct Iterable {
	public:
		Iterable(Iterator begin, Iterator end) : m_begin{ begin }, m_end{ end } {}

		Iterator begin()
		{
			return m_begin;
		}

		Iterator end()
		{
			return m_end;
		}

	private:
		Iterator m_begin;
		Iterator m_end;
	};
}
