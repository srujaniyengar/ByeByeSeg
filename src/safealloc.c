#define _GNU_SOURCE
#include "safealloc.h"

static Block *head = NULL;

Block *find_free(size_t size) {
    Block *curr = head;
    while (curr) {
        if (curr->is_free && curr->size >= size) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

Block *req_spc(size_t size) {
    Block *block;
    block = (Block *)sbrk(0);
    void *request = sbrk(size + BLOCK_SIZE);
    if (request == (void *)-1) {
        return NULL;
    }
    block->size = size;
    block->is_free = false;
    block->next = NULL;
    return block;
}

void *alloc(size_t size) {
    if (size == 0)
        return NULL;
    Block *block = find_free(size);
    if (block) {
        block->is_free = false;
        return (void *)(block + 1);
    }
    block = req_spc(size);
    if (!block)
        return NULL;
    if (!head) {
        head = block;
    } else {
        Block *curr = head;
        while (curr->next)
            curr = curr->next;
        curr->next = block;
    }
    return (void *)(block + 1);
}

void *safe_alloc(size_t size) {
    void *ptr = alloc(size);
    if (!ptr) {
        fprintf(stderr, "safe_alloc: allocation of %zu bytes failed\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *free_alloc(void *ptr) {
    if (ptr == NULL)
        return NULL;
    Block *block = (Block *)ptr - 1;
    block->is_free = true;
    return NULL;
}

void *re_alloc(size_t size, void *ptr) {
    if (ptr == NULL)
        return alloc(size);
    Block *block = (Block *)ptr - 1;
    if (block->size >= size)
        return ptr;
    void *new_ptr = alloc(size);
    if (!new_ptr)
        return NULL;
    memcpy(new_ptr, ptr, block->size);
    free_alloc(ptr);
    return new_ptr;
}

void *safe_realloc(size_t size, void *ptr) {
    void *new_ptr = re_alloc(size, ptr);
    if (!new_ptr) {
        fprintf(stderr, "safe_realloc: reallocation to %zu bytes failed\n", size);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

