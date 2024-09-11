//
// Created by xiehao on 2024/9/6.
//
#include "../../include/gc/mark_compact.h"

MarkCompact::MarkCompact(MemoryChunk *chunk) : m_mem_chunk(chunk) {

}

MarkCompact::~MarkCompact() {
    INFO_PRINT("[调用析构函数%s]释放资源\n", __func__);
}

MemoryChunk *MarkCompact::get_mem_chunk() {
    return m_mem_chunk;
}

MarkCompact *MarkCompact::set_mem_chunk(MemoryChunk *chunk) {
    m_mem_chunk = chunk;
    return this;
}

// ======

void MarkCompact::mark_step() {
    PRINT("\t 开始执行标记操作\n");

    /**
     * 模拟可达性分析算法标记对象, 回收未打标记的对象
     */
    list<MemoryCell *> *used_table = get_mem_chunk()->get_used_table();

    list<MemoryCell *>::iterator iterator;
    for (iterator = used_table->begin(); iterator != used_table->end(); iterator++) {
        MemoryCell *cell = *iterator;

        cell->to_string("模拟打标记");

        if (cell->get_size() == 4 && !cell->get_transfer_object()) {
            INFO_PRINT("\t 打上标记 \n");
            /**
             * 将打标记的对象放入transfer_table中，这个对象不能释放,释放了就无法实现内存移动，旧地址仍旧可以访问的功能
             */
            get_mem_chunk()->get_transfer_table()->push_front(cell);

            /**
             * 当前iterator重新设置为放入transfer_table中对象的克隆，为了防止后续操作将旧地址指向的对象释放了
             */
            *iterator = new MemoryCell(*cell);
        } else {
            INFO_PRINT("\t 未打上标记\n");
        }
    }
}

void MarkCompact::clean_step() {
    PRINT("\t 开始执行清理操作\n");

    bool flag = false;

    list<MemoryCell *>::iterator iterator;

    for (iterator = get_mem_chunk()->get_used_table()->begin(); iterator != get_mem_chunk()->get_used_table()->end();) {
        MemoryCell *cell = *iterator;
        cell->to_string("检测是否打了标记");

        /**
         * 释放未打标记的对象
         */
        if (!cell->get_mark()) {
            INFO_PRINT("\t 未打标记\n");

            /**
             * 处理used_table
             */
            iterator = get_mem_chunk()->get_used_table()->erase(iterator);

            /**
             * 处理available_table
             */
            get_mem_chunk()->get_available_table()->push_front(new MemoryCell(cell->get_start(), cell->get_size()));

            get_mem_chunk()->desc_used_cell_num(cell->get_size());

            /**
             * 释放对象
             */
            delete cell;

            flag = true;
        } else {
            INFO_PRINT("\t 打了标记， 无法回收\n");

            iterator++;
        };
    }

    if (!flag) {
        ERROR_PRINT("[GC后]没有可回收的内存,无法分配内存,执行Full GC\n");
        exit(1);
    }
}

void MarkCompact::memory_compact_before() {
    INFO_PRINT("[[向元素头部合并]] 开始\n");

    list<MemoryCell *>::iterator iterator = get_mem_chunk()->get_available_table()->begin();
    list<MemoryCell *>::iterator tmp_iterator;

    while (iterator != get_mem_chunk()->get_available_table()->end()) {

    }
}