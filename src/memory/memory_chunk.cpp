//
// Created by xiehao on 2024/9/6.
//

#include "../../include/common.h"
#include "memory_cell.h"
#include <list>

using namespace std;

class MemoryChunk {
private:
    /**
     * 创建Chunk的文件名
     */
    char *m_filename;

    /**
     * 创建Chunk的文件位置
     */
    uint m_line;
};

