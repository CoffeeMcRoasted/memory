#include <benchmark/benchmark.h>

#include <memory/pool_allocator.h>
#include <vector>

static void pool_allocator_alloc(benchmark::State& state)
{
    const int num_allocs = state.range(0);
    const int alloc_size = state.range(1);
    const int alignment = state.range(2);
    const int block_size = state.range(3);
    const int raw_memory_size = state.range(4);

    std::vector<uint8_t> raw_memory(raw_memory_size);
    memory::memory_address start;
    memory::memory_address end;

    start.raw = static_cast<void *>(&(*raw_memory.begin()));
    end.raw = static_cast<void *>(&(*raw_memory.end()));
    
    memory::alignment algnmnt = memory::select_upper_closest(alignment);
    
    memory::pool_allocator alloc(start, end, algnmnt, block_size);

    for (auto _ : state) 
    {
        for (int i = 0; i < num_allocs; i++) {
            auto blk = alloc.allocate(alloc_size);
            benchmark::DoNotOptimize(blk);
        }
        benchmark::ClobberMemory();

        state.PauseTiming();
        alloc.reset();
        benchmark::ClobberMemory();
        state.ResumeTiming();
    }

    state.counters["PerAlloc"] = benchmark::Counter(
      num_allocs * state.iterations(),
      benchmark::Counter::kIsRate | benchmark::Counter::kInvert);
}

BENCHMARK(pool_allocator_alloc)
    ->Args({100, 17, 32, 32, 3200})
    ->Args({1000, 17, 32, 32, 32000})
    ->Args({10000, 17, 32, 32, 320000});
BENCHMARK(pool_allocator_alloc)
    ->Args({100, 55, 32, 64, 6400})
    ->Args({1000, 55, 32, 64, 64000})
    ->Args({10000, 55, 32, 64, 640000});
BENCHMARK(pool_allocator_alloc)
    ->Args({100, 259, 32, 288, 28800})
    ->Args({1000, 259, 32, 288, 288000})
    ->Args({10000, 259, 32, 288, 2880000});