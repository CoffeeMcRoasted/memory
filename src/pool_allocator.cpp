#include <memory/pool_allocator.h>

#include "memory_utils.h"
#include <new>

namespace memory
{
    // Free list Block
    struct Block
    {
        Block* next;
    };

    memory_address pool_allocator::allocate(uint64_t size)
    {
        const memory_address tmp = m_current;
        m_current.raw = static_cast<void *>(static_cast<Block*>(m_current.raw)->next);
        return tmp;
    }

    void pool_allocator::deallocate(void* block, uint64_t size)
    {
        m_current.raw = static_cast<void*>(new(block) Block{static_cast<Block*>(m_current.raw)});
    }

    void pool_allocator::reset()
    {
        // TODO: Assert that block_size is bigger than a ptr (8 bytes in x64)
        //  e.g.: block_size > sizeof(block)
        const bool can_hold_a_block = m_end.idx > (m_start.idx + m_block_size);
        if(can_hold_a_block)
        {
            spdlog::info("Resetting pool allocator");
            m_current.idx = align(m_start.idx, m_alignment);
            Block* blck = new (m_current.raw) Block{nullptr};
            spdlog::info("Block addr: {0:x}, Next Block: {1:x}", (uint64_t)(void*)blck, (uint64_t)(void*)(blck->next));
            memory_address next_addr = m_current + m_block_size;
            spdlog::info("next_addr: {0:x}, m_end: {1:x}", next_addr.idx, m_end.idx);
            while (next_addr < m_end)
            {
                blck->next = new (next_addr.raw) Block{nullptr};
                spdlog::info("Block addr: {0:x}, Next Block: {1:x}", (uint64_t)(void*)blck, (uint64_t)(void*)(blck->next));
                blck = blck->next;
                next_addr.idx += m_block_size;
            }
            spdlog::info("Current Status:\nstart: {0:x}\nend: {1:x}\ncurrent: {2:x}\nBlockchain:\n", m_start.idx, m_end.idx, m_current.idx);
            Block* b= static_cast<Block*>(m_current.raw);
            while(b->next != nullptr)
            {
                spdlog::info("\tBlock {0:x} points to {1:x}", (uint64_t)(void*)b, (uint64_t)(void*)(b->next));
                b = b->next;
            }
        }
        else
        {
            m_current.raw = nullptr;
        }
        print_memory(m_start, m_end);
    }

    pool_allocator::pool_allocator(memory_address start, memory_address end, alignment alignment, uint64_t block_size)
        : m_start(start)
        , m_end(end)
        , m_alignment(alignment)
        , m_block_size(align(block_size, alignment))
    {
        // Create the free list.
        reset();
    }
}