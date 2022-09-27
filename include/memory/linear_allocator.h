#pragma once
#include <cstdint>
#include <cstddef>
#include <memory/memory_address.h>
#include <memory/alignment.h>

namespace memory
{
    class linear_allocator
    {
    public:
        memory_address allocate(uint64_t size, alignment alignment, uint64_t offset);
        inline void deallocate(void*);
        inline void reset() {m_current = m_start;}

        explicit linear_allocator(memory_address start, memory_address end);
        ~linear_allocator() = default;
    private:
        memory_address m_start;
        memory_address m_end;
        memory_address m_current;
    };
}