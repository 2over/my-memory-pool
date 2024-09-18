#include <iostream>
#include "include/memory/memory_pool.h"

void mark_copy() {

    MemoryPool *mem_pool = new MemoryPool();

    MemoryChunk *mem_chunk = mem_pool->new_chunk(78 * 2);

    // 模拟分的内存超过Chunk的大小
//    mem_chunk->malloc(80);
//    mem_chunk->malloc(81);

    // 模拟内存足够，能分到内存
    MemoryCell *cell1 = mem_chunk->malloc(8);
    MemoryCell *cell2 = mem_chunk->malloc(16);
    MemoryCell *cell3 = mem_chunk->malloc(32);
    MemoryCell *cell4 = mem_chunk->malloc(16);

    *((char *)cell3->ptr()) = 'a';
    *((char *)cell1->ptr()) = 'c';
    INFO_PRINT("%X=====>%c, %c\n", cell3->ptr(), *((char *)cell3->ptr()), *((char *)cell1->ptr()));

    // 模拟GC后因内存碎片，分不到内存
    mem_chunk->malloc(40);

    INFO_PRINT("%X=====>%c, %c\n", cell3->ptr(), *((char *)cell3->ptr()), *((char *)cell1->ptr()));

    // 模拟出发第二次GC
//    mem_chunk->malloc(40);
//
//    INFO_PRINT("%X=====>%c, %c\n", cell3->ptr(), *((char *)cell3->ptr()), *((char *)cell1->ptr()));

    mem_pool->print_chunks();

    delete mem_pool;
}

void mark_compact() {
    MemoryPool *mem_pool = new MemoryPool();

    MemoryChunk *mem_chunk = mem_pool->new_chunk(78);
    // 模拟内存足够能分到内存
    MemoryCell *cell1 = mem_chunk->malloc(8);
    MemoryCell *cell2 = mem_chunk->malloc(16);
    MemoryCell *cell3 = mem_chunk->malloc(32);
    MemoryCell *cell4 = mem_chunk->malloc(16);

    *((char *)cell3->ptr()) = 'a';
    INFO_PRINT("%X=======>%c\n", cell3, *((char *)cell3->ptr()));

    // 模拟GC后因内存碎片，分不到内存
    mem_chunk->malloc(40);

    PRINT("%X=======>%c\n", cell3->ptr(), *((char*) cell3->ptr()));

    mem_pool->print_chunks();

    delete mem_pool;

}

void mark_clean() {
    MemoryPool *mem_pool = new MemoryPool();

    MemoryChunk *mem_chunk = mem_pool->new_chunk(78);

    // 模拟内存足够，能分到内存
    MemoryCell *cell1 = mem_chunk->malloc(8);
    MemoryCell *cell2 = mem_chunk->malloc(16);
    MemoryCell *cell3 = mem_chunk->malloc(32);
    MemoryCell *cell4 = mem_chunk->malloc(16);

    // 模拟GC后因内存碎片，分不到内存
    mem_chunk->malloc(24);

    mem_pool->print_chunks();

    delete mem_pool;

}
int main() {

    switch (DEFAULT_GC_TYPE) {
        case GC_MARK_COLLECT: {
            mark_compact();
            break;
        }
        case GC_MARK_COPY: {
            mark_copy();
            break;
        }
        case GC_MARK_CLEAN: {
            mark_clean();
            break;
        }
    }
    return 0;
}

