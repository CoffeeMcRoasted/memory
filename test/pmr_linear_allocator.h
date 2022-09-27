#include <array>
#include <gtest/gtest.h>
#include <memory/pmr/linear_allocator.h>
#include <memory_resource>
#include <vector>


TEST(pmr_linear_allocator, std_vector)
{
    std::array<uint8_t, 2048> raw_memory {0};
    memory::memory_address start{.raw = static_cast<void *>(raw_memory.begin())};
    memory::memory_address end{.raw = static_cast<void *>(raw_memory.end())};
    memory::pmr::linear_allocator allocator(start, end);

    std::pmr::vector<uint64_t> vector{{1,2,3,4}, &allocator};

    vector.push_back(5);
    ASSERT_EQ(vector.capacity(), 8);
}