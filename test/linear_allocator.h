#include <array>
#include <gtest/gtest.h>
#include <memory/linear_allocator.h>



TEST(linear_allocator, allocate)
{
    std::array<uint8_t, 2048> raw_memory;
    memory::memory_address start{.raw = static_cast<void *>(raw_memory.begin())};
    memory::memory_address end{.raw = static_cast<void *>(raw_memory.end())};
    memory::linear_allocator alloc(start, end);
    void* allocated = alloc.allocate(128 * 8, memory::alignment::b64, 0);
    uint64_t* allocated_array = new(allocated) uint64_t[128];

    allocated_array[3] = 3;
    ASSERT_EQ(allocated_array[3], 3);

    alloc.reset();
}

TEST(linear_allocator, allocate_offset)
{
    std::array<uint8_t, 2048> raw_memory {0};
    memory::memory_address start{.raw = static_cast<void *>(raw_memory.begin())};
    memory::memory_address end{.raw = static_cast<void *>(raw_memory.end())};
    memory::linear_allocator alloc(start, end);

    void* allocated = alloc.allocate(64*8, memory::alignment::b64, 4);
    uint64_t* allocated_array = new(allocated) uint64_t[64];

    for(int i = 0; i < 64; i++)
    {
        allocated_array[i] = i;
    }
}
