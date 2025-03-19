#ifndef SAFEALLOC_H
#define SAFEALLOC_H
#define _GNU_SOURCE

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PAGE_SIZE 4096

typedef struct Block{
  size_t size;
  bool is_free;
  struct Block*next;
}Block;

#define BLOCK_SIZE sizeof(Block)
Block*find_free(size_t size);
Block*req_spc(size_t size);

void*safe_alloc(size_t size);
void*alloc(size_t size);
void*free_alloc(void *ptr);
void*safe_realloc(size_t size, void* ptr);
void*re_alloc(size_t size,void*ptr);
#endif  
