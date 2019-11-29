
#include "TestMemoryAllocator.h"

void test_MemoryAllocator_init(){
    size_t size = 512;
    void *memoryPool = malloc(size);
    MemoryAllocator *memory_allocator = MemoryAllocator_init(memoryPool, size);
    Print_MemoryAllocator(memory_allocator);

}
void test_MemoryAllocator_allocate(){
    size_t size = 512;
    size_t block_size = 40;
    void *memoryPool = malloc(size);
    MemoryAllocator *memory_allocator = MemoryAllocator_init(memoryPool, size);
    printf("new memory_allocator:\n\n ");
    Print_MemoryAllocator(memory_allocator);

    MemoryAllocator_allocate(memory_allocator,block_size);
    printf("after add block size %ld:\n\n ",block_size);
    Print_MemoryAllocator(memory_allocator);

}