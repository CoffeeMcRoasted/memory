#pragma once
#include <cstdint>

namespace memory
{
    enum class alignment : uint64_t
    {
        b4 = 4,
        b8 = 8,
        b16 = 16,
        b32 = 32,
        b64 = 64,
        b128 = 128,
        b256 = 256,
        b512 = 512,
        b4k = 4196,
    };

    inline constexpr uint64_t alignment_mask(alignment alignment)
    {
        return static_cast<uint64_t>(alignment) - 1u;
    }

    inline constexpr uint64_t align(uint64_t size, alignment alignment)
    {
        return (size + alignment_mask(alignment)) & ~alignment_mask(alignment);
    }

    constexpr alignment select_upper_closest(uint64_t align)
    {
        align--;
        align |= align >> 1;
        align |= align >> 2;
        align |= align >> 4;
        align |= align >> 8;
        align |= align >> 16;
        align++;
        return static_cast<alignment>(align);
    }

} // namespace memory
