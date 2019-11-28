

#include "MemoryAllocatorInterface.h"


MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size){

    MemoryAllocator* memory_allocator=malloc(sizeof(MemoryAllocator));
    assert(memory_allocator);
    if (memory_allocator) {
        memory_allocator->memoryPool = memoryPool;
        memory_allocator->size_memoryPool = size;

        /*allocate one block that Representing the  all memoryPool, that is initially freed */
        memory_allocator->number_of_blocks = 1;
        size_t metadata = size << 1;
        memory_allocator->memoryPool[0] = metadata;
    }
    return memory_allocator;

}

void* MemoryAllocator_allocate(MemoryAllocator* allocator,size_t size){
    /**allocate a new block in the memory Pool*/
    size_t block=PlatformAlignmentWidth;
    while((block<allocator->size_memoryPool) && !(PlatformAlignmentWidth & LSB) ){
        block+=allocator->memoryPool[PlatformAlignmentWidth>>1]+PlatformAlignmentWidth;


    }
    /*If  no free block (reached the end of the memory pool), return NULL.*/
    if(block<allocator->size_memoryPool){
        return  NULL;
    }
    else/*allocate a nre block*/
    {

    }

}