#include "alignment.h"
#include "linear_allocator.h"
#include "pmr_linear_allocator.h"
#include "pool_allocator.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}