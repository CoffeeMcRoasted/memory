#pragma once
#include <cstdint>
#include <cstddef>
#include <memory/memory_address.h>
#include <memory/alignment.h>

namespace memory
{
    class pool_allocator
    {
    public:
        memory_address allocate(uint64_t size);
        void deallocate(void* block, uint64_t size);
        void reset();

        explicit pool_allocator(memory_address start, memory_address end, alignment alignment, uint64_t block_size);
        ~pool_allocator() = default;
    private:
        memory_address m_start;
        memory_address m_end;
        memory_address m_current;
        alignment m_alignment;
        uint64_t m_block_size;
    };
}