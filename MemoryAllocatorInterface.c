#include "MemoryAllocatorInterface.h"


MemoryAllocator *MemoryAllocator_init(void *memoryPool, size_t size) {

    MemoryAllocator *memory_allocator = malloc(sizeof(MemoryAllocator));
    assert(memory_allocator);
    if (memory_allocator) {

        memory_allocator->memoryPool =  memoryPool;
        memory_allocator->size_memoryPool = size;

        /*allocate one block that Representing the  all memoryPool, that is initially freed */

        size_t metadata = (size - PlatformAlignmentWidth) << 1;
        memory_allocator->memoryPool[0] = metadata;
        printf("     **** Allocate a new memory allocator ****     \n\n\n");
    }
    return memory_allocator;

}

void *MemoryAllocator_allocate(MemoryAllocator *allocator, size_t size) {
    printf("memory_allocator->memoryPool %d \n", allocator->memoryPool);
    /**allocate a new block in the memory Pool*/
    size_t index = 0;/*size of the first block(metadata)*/
    size_t size_of_block;

    if (size % PlatformAlignmentWidth)/*todo:ceil dont work in c90?*/
        size = (size / PlatformAlignmentWidth + 1) * PlatformAlignmentWidth;

/*size=ceil((size/PlatformAlignmentWidth))*PlatformAlignmentWidth;*/

    /* while  reached the end of the memory pool and the blook is not free */
    while ((index < allocator->size_memoryPool) && (allocator->memoryPool[index] & LSB)) {
        size_of_block = (allocator->memoryPool[index]) >> 1;


        index += PlatformAlignmentWidth + size_of_block;/*next block index*/


    }
    printf("index: %ld \n", index);
    /*If  no free block (reached the end of the memory pool), return NULL.*/
    if (index >= allocator->size_memoryPool) {
        return NULL;
    } else/*allocate a new block*/
    {
        size_t last_size = (allocator->memoryPool[index]) >> 1;

        /*Insert the data into the free block*/

        size_t metadata = size << 1;/*enter the size of the new block to the metadata*/
        metadata |= 1;/*Mark that the  block is occupied*/
        allocator->memoryPool[index] = metadata;

        /*Insert the last block that marks the size that remains free*/
        metadata = last_size - PlatformAlignmentWidth - size;/*the size that remains free*/
        metadata <<= 1;/* the block  is free*/
        allocator->memoryPool[index + size + PlatformAlignmentWidth] = metadata;


    }
    return allocator->memoryPool;


}

void MemoryAllocator_free(MemoryAllocator *allocator, void *ptr) {
    /** get a pointer to block inside memoryPool and  free this  block,
     * if next adjacent block is free Merge them together*/

    printf("in free\n\n\nptr %d\n", (size_t *) ptr);
    printf("allocator->memoryPool %d\n", allocator->memoryPool);
    size_t block_index = ((size_t *) ptr - allocator->memoryPool);
    printf("block_index %d\n", block_index);
    size_t metadata = allocator->memoryPool[block_index];

    size_t size = metadata >> 1;
    size_t occupied = metadata & LSB;

    printf("in free :size =%d occupied=%d\n", size, occupied);
    if (occupied)/*if the block is occupied -free the block */
    {
        size_t next_block_index = block_index + PlatformAlignmentWidth + size;
        printf("next_block_index %d \n", next_block_index);
        size_t next_metadata_block = allocator->memoryPool[next_block_index];/*next block metadata*/
        if (!(next_metadata_block & LSB))/*if next  block is free ,Merge them together*/
        {
            printf("nex block is free \n");
            size += (next_metadata_block >> 1) + PlatformAlignmentWidth;

        }
        metadata = size << 1;/* mark the block as free*/
        allocator->memoryPool[block_index] = metadata;/*insert the block to the pool memory  */
    }

}

size_t MemoryAllocator_optimize(MemoryAllocator *allocator) {
    /**the function get pointer to allocator
     * and Merges all available blocks (adjacent to each other) and returns the size of the largest block*/

    printf("** in MemoryAllocator_optimize ** \n\n");
    size_t index = 0, next_index=0;/*size of the first block(metadata)*/
    size_t metadata, metadata_next_block;
    size_t size_block,occupied;
    size_t big_size_block_free = 0;
    /*Run across all the blocks up to One block before last*/
   do {


        metadata = allocator->memoryPool[index];
        size_block = metadata >> 1;
        occupied = metadata & LSB;
       printf("  block   size: %ld,occupied: %ld \n", size_block, occupied);
       printf(" PlatformAlignmentWidth + size_block %d \n", PlatformAlignmentWidth + size_block);
        next_index += PlatformAlignmentWidth + size_block;/*next block index*/

        printf("next_index %d \n",next_index);
        metadata_next_block = allocator->memoryPool[next_index];
        printf("next size block: %ld,occupied: %ld \n", metadata_next_block>>1, metadata_next_block&LSB);
printf("occupied %d metadata_next_block & LSB %d if: %d ",occupied,metadata_next_block & LSB,(!occupied && !(metadata_next_block & LSB)));
        if (!occupied && !(metadata_next_block & LSB)) {/*If the next block is also free -adjacent to each other*/
            printf("in if!!!!!!!!!!!!\n\n");
            size_block += metadata_next_block >> 1 + PlatformAlignmentWidth;
            metadata = size_block << 1;
            allocator->memoryPool[index] = metadata;
        }
        if (big_size_block_free< size_block)
            big_size_block_free=size_block;
            index = next_index;


    } while (index +(allocator->memoryPool[index]>>1)< allocator->size_memoryPool);
    if (big_size_block_free< size_block)/*check the last block size*/
        big_size_block_free=size_block;
    return big_size_block_free;
}

void *MemoryAllocator_release(MemoryAllocator *allocator) {
    /** release allocator*/
    free(allocator->memoryPool);/*free the memoryPool*/
    free(allocator);/*free allocator*/
    printf(" \n\n    **** release allocator****     \n\n\n");
    return allocator->memoryPool;

}

void Print_MemoryAllocator(MemoryAllocator *allocator) {
    /** get a pointer to MemoryAllocator and print the memory Pool ,print all block metadata**/


    size_t index = 0;/*size of the first block(metadata)*/
    size_t metadata;
    size_t size_of_block;
    size_t occupied;
    printf("\nstatus of memory: \n\n");
    while (index < allocator->size_memoryPool) {

        metadata = allocator->memoryPool[index];
        size_of_block = metadata >> 1;
        occupied = metadata & LSB;
        printf("size block: %ld,occupied: %ld \n", size_of_block, occupied);

        index += PlatformAlignmentWidth + size_of_block;/*next block index*/


    }
}
