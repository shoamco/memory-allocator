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


/**MemoryAllocator  */
struct MemoryAllocator {
    size_t *memoryPool;
    size_t size_memoryPool;


};


/**initialize Memory Allocator */
MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size);




/** release allocator*/
void* MemoryAllocator_release(MemoryAllocator* allocator);


/** free block,if next adjacent block is free Merge them together*/
void MemoryAllocator_free(MemoryAllocator* allocator, void*ptr);

/**Allocate a new block in memoryPool*/
void* MemoryAllocator_allocate(MemoryAllocator* allocator,size_t size);

/**optimize-Merges all available blocks (adjacent to each other) and returns the size of the largest block*/
size_t MemoryAllocator_optimize(MemoryAllocator* allocator);


/** get a pointer to MemoryAllocator and print the memory Pool ,print all block metadata**/
void Print_MemoryAllocator(MemoryAllocator* allocator);
#endif /*MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H*/