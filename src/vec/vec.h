//
// Created by erickth on 24/05/23.
//

#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "../defs.h"
#include "../log.h"

struct vec_t {
	i64 *buffer;
	usize len;
	usize cap;
};

enum result {
	OK,
	GROW_FAILURE,
	SHRINK_FAILURE,
	ALLOC_ERROR,
	OUT_OF_BOUNDS,
	NULL_PTR
};

struct vec_t vec_new(void);
struct vec_t vec_new_with_capacity(usize cap);
bool vec_is_overly_large(struct vec_t *vec);
enum result vec_set_val(struct vec_t *vec, usize index, i64 val);
enum result vec_append(struct vec_t *vec, i64 val);
enum result vec_insert(struct vec_t *vec, usize index, i64 val);
enum result vec_pop(struct vec_t *vec, i64 *out);
enum result vec_remove(struct vec_t *vec, usize index, i64 *out);
enum result vec_grow(struct vec_t *vec);
enum result vec_shrink(struct vec_t *vec);
enum result vec_print(struct vec_t *vec);
void vec_deinitialise(struct vec_t *vec);
/// Macro to make using the vec_shrink function easier, as otherwise we have to
/// always handle the error manually
#define shrink_vec(vec)                                                        \
	do {                                                                       \
		enum result shrink_res = vec_shrink(vec);                              \
		if (shrink_res != OK) {                                                \
			return shrink_res;                                                 \
		}                                                                      \
	} while (0)

#endif // VEC_H
