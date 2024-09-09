#include <iostream>
#include "include/memory/memory_pool.h"
int main() {

    MemoryPool *mem_pool = new MemoryPool();

    MemoryChunk *mem_chunk = mem_pool->new_chunk(78);

    MemoryCell *cell1 = mem_chunk->malloc(8);
    MemoryCell *cell2 = mem_chunk->malloc(16);
    MemoryCell *cell3 = mem_chunk->malloc(32);
    MemoryCell *cell4 = mem_chunk->malloc(32);

    *((char *) cell3->ptr()) = 'a';

    INFO_PRINT("%X========>%c\n", cell3, *((char*)cell3->ptr()));

    mem_chunk->malloc(40);

    PRINT("%X======>%c\n", cell3->ptr(), *((char*)cell3->ptr()));

    mem_pool->print_chunks();
    delete mem_pool;

    return 0;

}

