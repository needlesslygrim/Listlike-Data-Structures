//
// Created by erickth on 24/05/23.
//

#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include <log.h>
#include <defs.h>

/// A growable array type.
struct vec_t {
	i64 *buffer;
	usize len;
	usize cap;
};
/// Create a new vector, does not allocate on the heap at all
struct vec_t vec_new(void);
/// Create a new vector with a set capacity, allocates on the heap
struct vec_t vec_new_with_capacity(usize cap);

/// Gets the value of the vec at a given index,
void vec_get_at(struct vec_t *vec, usize index, i64 *out);
/// Set the value of the vec at a given index
void vec_set_at(struct vec_t *vec, usize index, i64 val);

/// Append a value to the end of the vec
void vec_append(struct vec_t *vec, i64 val);
/// Inserts a value at a given index
void vec_insert(struct vec_t *vec, usize index, i64 val);
/// Pop the last value off the vector, optional `out` parameter to capture that
/// end value.
void vec_pop(struct vec_t *vec, i64 *out);
/// Remove a value at a given index, optional `out` parameter to capture the value at that index.
void vec_remove(struct vec_t *vec, usize index, i64 *out);

/// Grow the vec, not meant to be used outside of library
void vec_grow(struct vec_t *vec);
/// Grow the vec to a specific capacity, meant to be used outside of library
void vec_grow_to(struct vec_t *vec, usize cap);
/// Shrink the vec, not meant to be used outside of library
void vec_shrink(struct vec_t *vec);
/// Check if the vec is overly large, not meant to be used outside of library
bool vec_is_overly_large(struct vec_t *vec);

/// Print the vec to stdout, will be formatted nicely
void vec_print(struct vec_t *vec);

/// Deinitialise a vector, vector will become invalid after using this
void vec_deinitialise(struct vec_t *vec);
#endif // VEC_H
