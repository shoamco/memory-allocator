

#include "MemoryAllocatorInterface.h"


MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size){

    MemoryAllocator* memory_allocator=malloc(sizeof(MemoryAllocator));
    assert(memory_allocator);
    if (memory_allocator) {
        memory_allocator->memoryPool = memoryPool;
        memory_allocator->size_memoryPool = size;

        /*allocate one block that Representing the  all memoryPool, that is initially freed */
        memory_allocator->blocks =  (Block*) malloc( sizeof(Block*));
        memory_allocator->number_of_blocks=1;
        Block* block=malloc(sizeof(Block));
        assert(block);
        if (block) {
            memory_allocator->blocks[0] =block;

            printf("*** initialize Memory Allocator ***\n");
        }
        else{
            free(memory_allocator);/*if allocation fall -free memory_allocator */
            memory_allocator = NULL;/*return null for the user*/
        }

    }
    return memory_allocator;

}

void* MemoryAllocator_allocate(MemoryAllocator* allocator,size_t size){
    /**allocate a new block in the memory Pool*/

    Block* block=malloc(sizeof(Block));
    assert(block);
    if (block) {
        /*create a new block and add it into the memoryPool */
//        block->metadata = memoryPool;
        block->size_block = size;
        allocator->number_of_blocks+=1;
        allocator->blocks=realloc( allocator->blocks, allocator->number_of_blocks);


        printf("*** initialize Memory Allocator ***\n");
    }

}