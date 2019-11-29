

#include "MemoryAllocatorInterface.h"


MemoryAllocator *MemoryAllocator_init(void *memoryPool, size_t size) {

    MemoryAllocator *memory_allocator = malloc(sizeof(MemoryAllocator));
    assert(memory_allocator);
    if (memory_allocator) {
        memory_allocator->memoryPool = memoryPool;
        memory_allocator->size_memoryPool = size;

        /*allocate one block that Representing the  all memoryPool, that is initially freed */
        memory_allocator->number_of_blocks = 1;
        size_t metadata = (size-PlatformAlignmentWidth) << 1;
        memory_allocator->memoryPool[0] = metadata;
        printf("**** Allocate a new memory allocator ****\n");
    }
    return memory_allocator;

}

void *MemoryAllocator_allocate(MemoryAllocator *allocator, size_t size) {
    /**allocate a new block in the memory Pool*/
    size_t index = 0;/*size of the first block(metadata)*/
    size_t size_of_block;
    /* while  reached the end of the memory pool and the blook is not free */
    while ((index < allocator->size_memoryPool) && !(allocator->memoryPool[index] & LSB)) {
        size_of_block = (allocator->memoryPool[index]) >> 1;
        index += PlatformAlignmentWidth + size_of_block;/*next block index*/


    }
    /*If  no free block (reached the end of the memory pool), return NULL.*/
    if (index >= allocator->size_memoryPool) {
        return NULL;
    } else/*allocate a new block*/
    {
        size_t last_size = allocator->memoryPool[index];

        /*Insert the data into the free block*/
        size_t metadata = size << 1;/*enter the size of the new block to the metadata*/
        metadata |= 1;/*Mark that the  block is occupied*/
        allocator->memoryPool[index] = metadata;

        /*Insert the last block that marks the size that remains free*/
        metadata = last_size - PlatformAlignmentWidth - size;/*the size that remains free*/
        metadata <<= 1;/* the block  is free*/
        allocator->memoryPool[index + size] = metadata;


    }

}

void print_memoryPool(MemoryAllocator *allocator) {
    size_t index = 0;/*size of the first block(metadata)*/
    size_t metadata;
    size_t size_of_block;
    size_t free;
    printf("status of memory: \n");
    while (index < allocator->size_memoryPool) {

        metadata = allocator->memoryPool[index];
        size_of_block = metadata >> 1;
        free = metadata & LSB;
        printf("size block: %d,free: %d \n",size_of_block,free);

        index += PlatformAlignmentWidth + size_of_block;/*next block index*/


    }
}