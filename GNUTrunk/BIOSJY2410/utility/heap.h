/*
 * vivi/include/heap.h
 *
 * Based on bootldr/heap.h
 *
 */
//taken from vivi

#include <types.h>

int heap_init(void);
void *malloc(__u32 size);
void free(void *block);


