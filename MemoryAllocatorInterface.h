

#ifndef MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H
#define MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include <assert.h>
#include <stdlib.h>
typedef struct MemoryAllocator MemoryAllocator;
typedef struct Block Block;



/**Block in memory pool  */
struct Block {
    /*metadata contain the size of the block+ bit for free/occupied (LSB = metadata & 1)*/
    size_t metadata;
    size_t size_block;
};
/**MemoryAllocator  */
struct MemoryAllocator {
    void* memoryPool;
    size_t size_memoryPool;
    Block **blocks; /*array of block*/
    size_t number_of_blocks;

};


/**initialize Memory Allocator */
MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size);


/* Returns a ptr to the memoryPool */
void* MemoryAllocator_release(MemoryAllocator* allocator);

/* Merge the next adjacent block is free */
void MemoryAllocator_free(MemoryAllocator* allocator, void*ptr);

void* MemoryAllocator_allocate(MemoryAllocator* allocator,size_t size);
/* Merges all adjacent free blocks, and returns the size of largest free block */

size_t MemoryAllocator_optimize(MemoryAllocator* allocator);

#endif /*MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H*/