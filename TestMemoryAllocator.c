
#include "TestMemoryAllocator.h"

void test_MemoryAllocator_init() {
    printf("\n\n\n\n******   test_MemoryAllocator_init    ******\n\n\n\n");
    size_t size = 512;
    void *memoryPool = malloc(size);
    MemoryAllocator *memory_allocator = MemoryAllocator_init(memoryPool, size);
    Print_MemoryAllocator(memory_allocator);
    memoryPool = MemoryAllocator_release(memory_allocator);


}

void test_MemoryAllocator_allocate() {
    printf("\n\n\n\n******   test_MemoryAllocator_allocate    ******\n\n\n\n");
    size_t size = 512;
    size_t block_size = 33;
    void *memoryPool = malloc(size);
    MemoryAllocator *memory_allocator = MemoryAllocator_init(memoryPool, size);
    printf("new memory_allocator:\n\n ");
    Print_MemoryAllocator(memory_allocator);


    memoryPool=MemoryAllocator_allocate(memory_allocator, block_size);
    printf("after add block size %ld:\n\n ", block_size);
   Print_MemoryAllocator(memory_allocator);

    block_size = 47;
    memoryPool=MemoryAllocator_allocate(memory_allocator, block_size);
    printf("2after add block size %ld:\n\n ", block_size);
    Print_MemoryAllocator(memory_allocator);


    memoryPool =MemoryAllocator_release(memory_allocator);

}
void test_MemoryAllocator_free(){
    printf("\n\n\n\n******   test_MemoryAllocator_free    ******\n\n\n\n");
    size_t size = 512;
    size_t block_size = 33;
    void *memoryPool = malloc(size);
    printf("memoryPool %ld:\n\n ", memoryPool);
    MemoryAllocator *memory_allocator = MemoryAllocator_init(memoryPool, size);
    printf("new memory_allocator:\n\n ");
    Print_MemoryAllocator(memory_allocator);


    memoryPool=  MemoryAllocator_allocate(memory_allocator, block_size);
    printf("after add block size %ld:\n\n ", block_size);
    Print_MemoryAllocator(&memory_allocator);

    block_size = 47;
    memoryPool= MemoryAllocator_allocate(memory_allocator, block_size);
    printf("after add block size %ld:\n\n ", block_size);

    Print_MemoryAllocator(memory_allocator);


    void* ptr=memory_allocator->memoryPool+48;

    MemoryAllocator_free(memory_allocator,ptr);
    printf("after free  %ld:\n\n ");
    Print_MemoryAllocator(memory_allocator);

    ptr=memory_allocator->memoryPool+8;
    MemoryAllocator_free(memory_allocator,ptr);
    printf("after free  %ld:\n\n ");
    Print_MemoryAllocator(memory_allocator);

    memoryPool =MemoryAllocator_release(memory_allocator);
}
void test_MemoryAllocator_optimize(){
    printf("\n\n\n\n******   test_MemoryAllocator_optimize    ******\n\n\n\n");
    size_t size = 512;
    size_t block_size = 33;
    void *memoryPool = malloc(size);
    printf("memoryPool %ld:\n\n ", memoryPool);
    MemoryAllocator *memory_allocator = MemoryAllocator_init(memoryPool, size);
    printf("new memory_allocator:\n\n ");
    Print_MemoryAllocator(memory_allocator);


    memoryPool=  MemoryAllocator_allocate(memory_allocator, block_size);
    printf("after add block size %ld:\n\n ", block_size);
    Print_MemoryAllocator(&memory_allocator);

    block_size = 47;
    memoryPool= MemoryAllocator_allocate(memory_allocator, block_size);
    printf("after add block size %ld:\n\n ", block_size);

    Print_MemoryAllocator(memory_allocator);


    size_t big_size_block_free;

    big_size_block_free=MemoryAllocator_optimize(memory_allocator);
    printf("big_size_block_free %d\n",big_size_block_free);
    Print_MemoryAllocator(&memory_allocator);


    memoryPool =MemoryAllocator_release(memory_allocator);
}