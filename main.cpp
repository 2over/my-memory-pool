#include <iostream>
#include "include/memory/memory_pool.h"

int main() {

    MemoryPool *mem_pool = new MemoryPool();

    MemoryChunk *mem_chunk = mem_pool->new_chunk(78 * 2);

    // 模拟能分到内存
    MemoryCell *cell1 = mem_chunk->malloc(8);
    MemoryCell *cell2 = mem_chunk->malloc(16);
    MemoryCell *cell3 = mem_chunk->malloc(32);
    MemoryCell *cell4 = mem_chunk->malloc(16);

    *((char *) cell3->ptr()) = 'a';
    *((char *) cell1->ptr()) = 'c';

    INFO_PRINT("%X========>%c, %c\n", cell3->ptr(), *((char *) cell3->ptr()), *((char *) cell1->ptr()));

    // 模拟GC后因内存碎片，分不到内存
    mem_chunk->malloc(40);

    PRINT("%X======>%c, %c\n", cell3->ptr(), *((char *) cell3->ptr()), *((char *) cell1->ptr()));

    mem_pool->print_chunks();
    delete mem_pool;

    return 0;

}

