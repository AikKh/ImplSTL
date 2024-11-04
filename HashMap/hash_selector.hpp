#include <iostream>
#include <cstdint>

constexpr uint32_t compile_time_seed()
{
    const char* time_str = __TIME__;
    uint32_t seed = 0;
    for (int i = 0; time_str[i] != '\0'; ++i)
    {
        seed = (seed * 10) + (time_str[i] - '0');
    }
    return seed;
}

constexpr uint32_t lcg(uint32_t seed)
{
    return (seed * 1664525u + 1013904223u);
}

template<size_t N>
constexpr size_t random_index()
{
    return lcg(compile_time_seed()) % N;
}

template<typename Ret, typename... Args>
struct RandomSelector {
    using FuncType = Ret(*)(Args...);

    template<FuncType... Functions>
    struct Selector {
        static constexpr FuncType functions[] = { Functions... };
        static constexpr size_t index = random_index<sizeof...(Functions)>();

        static constexpr FuncType selected_function = functions[index];

        static Ret Call(Args... args)
        {
            return selected_function(std::forward<Args>(args)...);
        }
    };
};
