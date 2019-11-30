

#ifndef MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H
#define MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define  PlatformAlignmentWidth 8
#define LSB 1
typedef struct MemoryAllocator MemoryAllocator;
typedef struct Block Block;
/**
          Memory allocation service

 * */


/**Block in memory pool  */
struct Block {
    /*metadata contain the size of the block+ bit for free/occupied(0/1) (LSB = metadata & 1)*/
    size_t metadata;
    size_t size_block;
};
/**MemoryAllocator  */
struct MemoryAllocator {
    size_t *memoryPool;
    size_t size_memoryPool;
    size_t number_of_blocks;
/*    Block **blocks;
   */

};


/**initialize Memory Allocator */
MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size);


/* Returns a ptr to the memoryPool */
/** release-free memoryPool and all blocks inside*/
/** release allocator*/
void* MemoryAllocator_release(MemoryAllocator* allocator);


/** free block,if next adjacent block is free Merge them together*/
void MemoryAllocator_free(MemoryAllocator* allocator, void*ptr);

/**Allocate a new block in memoryPool*/
void* MemoryAllocator_allocate(MemoryAllocator* allocator,size_t size);
/* Merges all adjacent free blocks, and returns the size of largest free block */

size_t MemoryAllocator_optimize(MemoryAllocator* allocator);


void Print_MemoryAllocator(MemoryAllocator* allocator);
#endif /*MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H*/
