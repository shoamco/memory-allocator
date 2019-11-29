
#include "TestMemoryAllocator.h"

void test_MemoryAllocator_init(){
    size_t size = 512;
    void *memoryPool = malloc(size);
    MemoryAllocator *memory_allocator = MemoryAllocator_init(memoryPool, size);
    print_memoryPool(memory_allocator);

}