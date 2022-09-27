#include <array>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <memory/pool_allocator.h>

class pool_allocator_test : public ::testing::Test
{
protected:
    pool_allocator_test()
    {
        raw_memory.fill(0);
        start.raw = static_cast<void *>(raw_memory.begin());
        end.raw = static_cast<void *>(raw_memory.end());
        spdlog::info("Test memory allocated at start: {0:x}, end: {1:x}", start.idx, end.idx);
    };

    void print_test_memory()
    {
    for(memory::memory_address i = start; i < end; i.idx++)
    {
        spdlog::info("Address: {0:x}\tContent: {1:x}", i.idx, *static_cast<uint8_t*>(i.raw));
    }
}

    void SetUp() override
    {
        for(auto& byte : raw_memory)
            byte = 0;
    }

    std::array<uint8_t, 512> raw_memory;
    memory::memory_address start;
    memory::memory_address end;
    
};

// TEST(pool_allocator, setup)
// {
//     struct matrix3x3
//     {
//         float m[9];
//     };
    
//     std::array<uint8_t, 2048> raw_memory;
//     memory::memory_address start{.raw = static_cast<void *>(raw_memory.begin())};
//     memory::memory_address end{.raw = static_cast<void *>(raw_memory.end())};
//     memory::alignment alignment = memory::select_upper_closest(sizeof(float));
//     uint64_t block_size =  sizeof(matrix3x3);

//     memory::pool_allocator alloc(start, end, alignment, block_size);
//     ASSERT_NE(alloc.allocate(sizeof(matrix3x3)), nullptr);
// }

TEST_F(pool_allocator_test, allocate)
{
    struct matrix3x3
    {
        int m[9];
    };
    
    memory::alignment alignment = memory::select_upper_closest(sizeof(int));
    uint64_t block_size =  sizeof(matrix3x3);
    
    memory::pool_allocator alloc(start, end, alignment, block_size);
    int* allocated_array = (int*)alloc.allocate(sizeof(int)*3).raw;

    allocated_array[3] = 3;
    ASSERT_EQ(allocated_array[3], 3);
}

TEST_F(pool_allocator_test, allocate10)
{
    struct matrix3x3
    {
        int m[9];
    };
    
    memory::alignment alignment = memory::select_upper_closest(sizeof(int));
    uint64_t block_size =  sizeof(matrix3x3);
    
    memory::pool_allocator alloc(start, end, alignment, block_size);
    for (int i = 0; i < 10; ++i)
    {
        matrix3x3* allocated_matrix = (matrix3x3*)alloc.allocate(sizeof(matrix3x3)).raw;
        for(int j = 0; j < 9; ++j)
        {
            allocated_matrix->m[j] = 9;
        }
        ASSERT_EQ(allocated_matrix->m[3], 9);
    }

    print_test_memory();
    
}

// TEST(linear_allocator, allocate_offset)
// {
//     std::array<uint8_t, 2048> raw_memory {0};
//     memory::memory_address start{.raw = static_cast<void *>(raw_memory.begin())};
//     memory::memory_address end{.raw = static_cast<void *>(raw_memory.end())};
//     memory::linear_allocator alloc(start, end);

//     void* allocated = alloc.allocate(64*8, memory::alignment::b64, 4);
//     uint64_t* allocated_array = new(allocated) uint64_t[64];

//     for(int i = 0; i < 64; i++)
//     {
//         allocated_array[i] = i;
//     }
// }
