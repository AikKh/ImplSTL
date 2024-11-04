namespace atl
{
	template<typename T>
	class DefaultAllocator {
	public:
		DefaultAllocator() = default;

		T* allocate(const size_t n) const
		{
			if (n == 0)
			{
				return nullptr;
			}

			void* const pv = calloc(n, sizeof(T));
			if (!pv)
			{
				throw std::bad_alloc();
			}

			return static_cast<T*>(pv);
		}

		void deallocate(T* const p, size_t) const noexcept
		{
			if (p)
			{
				free(p);
			}
		}
	};
}