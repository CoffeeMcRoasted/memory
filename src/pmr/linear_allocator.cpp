#include <memory/pmr/linear_allocator.h>

namespace memory
{
    namespace pmr
    {
        linear_allocator::linear_allocator(memory::memory_address start, memory::memory_address end)
            : m_allocator(start, end)
        {}
        
        void* linear_allocator::do_allocate(size_t size, size_t alignment) 
        {
            return m_allocator.allocate(size, memory::select_upper_closest(alignment), 0);
        }

        void linear_allocator::do_deallocate(void*, size_t, size_t)
        {}

        bool linear_allocator::do_is_equal(std::pmr::memory_resource const&) const noexcept
        {
            return false;
        };
    }
}