#include "memory_utils.h"

#include <spdlog/spdlog.h>

namespace memory
{
    void print_memory(memory_address begin, memory_address end)
    {
        for(memory_address i = begin; i < end; i.idx++)
        {
            spdlog::info("Address: {0:x}\tContent: {1:x}", i.idx, *(static_cast<uint8_t*>(i.raw)));
        }
    }
}