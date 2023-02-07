#pragma once

/* Require an externally linked heap implementation to be provided if fake heap isn't used. */
#ifndef EXL_USE_FAKEHEAP

#include <cstddef>

extern "C" {

extern void *malloc(size_t size);
extern void *realloc(void *ptr, size_t new_size);
extern void *aligned_alloc( size_t alignment, size_t size );

extern void free(void *ptr);

};

#endif