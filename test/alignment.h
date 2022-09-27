#include <gtest/gtest.h>
#include <memory/alignment.h>

TEST(alignment, alignment)
{
    uint64_t pointer_value = 0;
    uint64_t offset = 4;
    memory::alignment alignment =  memory::alignment::b8;

    ASSERT_EQ(memory::align(pointer_value + offset, alignment), 8);
}

TEST(alignment, alignment_offset)
{
    uint64_t pointer_value =1024;
    uint64_t offset = 8;
    memory::alignment alignment =  memory::alignment::b64;

    ASSERT_EQ(memory::align(pointer_value + offset, alignment), 1088);
}
