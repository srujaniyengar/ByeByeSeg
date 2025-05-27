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

// === MMAP Allocator ===

void* mmap_alloc(size_t size) {
    if (size == 0)
        return NULL;
    // Align size to PAGE_SIZE
    size_t total_size = ((size - 1) / PAGE_SIZE + 1) * PAGE_SIZE;
    void* ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;
    return ptr;
}

void* safe_mmap_alloc(size_t size) {
    void* ptr = mmap_alloc(size);
    if (!ptr) {
        fprintf(stderr, "safe_mmap_alloc: mmap allocation of %zu bytes failed\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void mmap_free(void* ptr, size_t size) {
    if (!ptr || size == 0)
        return;
    size_t total_size = ((size - 1) / PAGE_SIZE + 1) * PAGE_SIZE;
    if (munmap(ptr, total_size) == -1) {
        perror("mmap_free: munmap failed");
    }
}
