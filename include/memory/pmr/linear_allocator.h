#pragma once
#include <cstdint>
#include <cstddef>
#include <memory_resource>
#include <memory/memory_address.h>
#include <memory/alignment.h>
#include <memory/linear_allocator.h>

namespace memory
{
    namespace pmr
    {
        class linear_allocator : public std::pmr::memory_resource
        {
        public:
            linear_allocator(memory::memory_address start, memory::memory_address end);
            virtual ~linear_allocator() = default;
            linear_allocator(linear_allocator const&) = delete;
            linear_allocator& operator=(linear_allocator const&) = delete;

        private:
            virtual void* do_allocate(size_t size, size_t alignment);

            virtual void do_deallocate(void*, size_t, size_t);

            virtual bool do_is_equal(std::pmr::memory_resource const&) const noexcept;

            memory::linear_allocator m_allocator;
        };
    }
}