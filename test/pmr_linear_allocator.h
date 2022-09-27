#include <array>
#include <gtest/gtest.h>
#include <memory/linear_allocator.h>
#include <memory_resource>
#include <vector>

class LinearAllocator : public std::pmr::memory_resource
{
public:
    LinearAllocator(memory::memory_address start, memory::memory_address end)
        : m_allocator(start, end)
    {}
    ~LinearAllocator() = default;
    LinearAllocator(LinearAllocator const&) = delete;
    LinearAllocator& operator=(LinearAllocator const&) = delete;

private:
    virtual void* do_allocate(size_t size, size_t alignment) 
    {
        return m_allocator.allocate(size, memory::select_upper_closest(alignment), 0);
    }
    virtual void do_deallocate(void*, size_t, size_t) {}

    virtual bool do_is_equal(std::pmr::memory_resource const&) const noexcept
    {
        return false;
    };
    memory::linear_allocator m_allocator;
};

TEST(pmr_linear_allocator, std_vector)
{
    std::array<uint8_t, 2048> raw_memory {0};
    memory::memory_address start{.raw = static_cast<void *>(raw_memory.begin())};
    memory::memory_address end{.raw = static_cast<void *>(raw_memory.end())};
    LinearAllocator allocator(start, end);

    std::pmr::vector<uint64_t> vector{{1,2,3,4}, &allocator};

    vector.push_back(5);
    ASSERT_EQ(vector.capacity(), 8);
}