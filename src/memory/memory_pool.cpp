//
// Created by xiehao on 2024/9/6.
//


#include "../../include/memory/memory_pool.h"

MemoryPool::~MemoryPool()
{
    INFO_PRINT("[调用析构函数]%s\n", __func__);

    free_chunks();
}

// ===========

MemoryChunk *MemoryPool::new_chunk(uint mem_size)
{
    MemoryChunk *mem_chunk = new MemoryChunk(mem_size, __FILE__, __LINE__);
    this->m_chunks.push_front(mem_chunk);

    return mem_chunk;
}

// =========

void MemoryPool::print_chunks()
{
    INFO_PRINT("[打印未释放的内存]开始\n")
}

