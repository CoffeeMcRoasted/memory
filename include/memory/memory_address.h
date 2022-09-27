#pragma once

#include <cstdint>

namespace memory
{
    struct memory_address
    {
        union
        {
            void *raw;
            uintptr_t idx;
        };

        friend memory_address operator+(memory_address address, uint64_t size)
        {
            return memory_address{.idx = address.idx + size};
        }

        friend memory_address operator-(memory_address address, uint64_t size)
        {
            return memory_address{.idx = address.idx - size};
        }

        friend uint64_t operator-(memory_address lhs, memory_address rhs)
        {
            return lhs.idx - rhs.idx;
        }

        operator void *() { return raw; }
    };

}
