#ifndef _TASK_H_
#define _TASK_H_

#include "start_task.h"

#include "led_task.h"

#include "float_task.h"

#include "protocol_task.h"

extern OS_MEM  my_mem;
#define MY_MEM_NUM  5
//每个存储块大小
//由于一个指针变量占用4字节所以块的大小一定要为4的倍数
//而且必须大于一个指针变量(4字节)占用的空间,否则的话存储块创建不成功

#define MY_MEMBLOCK_SIZE  100

#endif
