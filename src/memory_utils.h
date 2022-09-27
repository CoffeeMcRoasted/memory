#pragma once

#include <memory/alignment.h>
#include <memory/memory_address.h>
#include <spdlog/spdlog.h>


namespace memory
{
    void print_memory(memory_address begin, memory_address end);
}