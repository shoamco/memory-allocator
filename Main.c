
/*
 * git add .gitignore

  gcc Main.c MemoryAllocator.h MemoryAllocator.c  -lgtest -lgtest_main -pthread -o test

 */
#include "MemoryAllocatorInterface.h"
#include "TestMemoryAllocator.h"

int main() {

    /*test_MemoryAllocator_init();*/
   /* test_MemoryAllocator_allocate();*/
   /* test_MemoryAllocator_allocate();*/
  /* test_MemoryAllocator_free();*/
  test_MemoryAllocator_optimize();
    return 0;
}