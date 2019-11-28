

#ifndef MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H
#define MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct MemoryAllocator MemoryAllocator;
/* memoryPool is a ptr to an already-existing large memoryblock */

MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size);

/* Returns a ptr to the memoryPool */
void* MemoryAllocator_release(MemoryAllocator* allocator);

/* Merge the next adjacent block is free */
void MemoryAllocator_free(MemoryAllocator* allocator, void*ptr);

/* Merges all adjacent free blocks, and returns the size of largest free block */

size_t MemoryAllocator_optimize(MemoryAllocator* allocator);

#endif /*MEMORY_MEMORY_ALLOCATOR_SHOAMCO_MEMORYALLOCATOR_H*/
