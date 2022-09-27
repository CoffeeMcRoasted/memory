#include <memory/linear_allocator.h>

namespace memory
{
    linear_allocator::linear_allocator(memory_address start, memory_address end)
        : m_start(start)
        , m_end(end)
        , m_current(start)
    {}

    memory_address linear_allocator::allocate(uint64_t size, alignment alignment, uint64_t offset)
    {
        // TODO: This is not threadsafe
        // Offset and align the current pointer, and offset back
        m_current.idx = align(m_current.idx + offset, alignment) - offset;
        memory_address tmp = m_current;
        m_current.idx += size;

        if(m_current > m_end)
        {
            return memory_address{nullptr};
        }

        return tmp;
    }

    void linear_allocator::deallocate(void *)
    {
        // no-op
    }
}