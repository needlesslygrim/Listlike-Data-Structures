//
// Created by erickth on 24/05/23.
//

#ifndef LIST_VEC_H
#define LIST_VEC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct vec_t {
	int64_t *data;
	size_t len;
	size_t cap;
};

enum result { OK, OUT_OF_BOUNDS, RESIZE_FAILURE };

struct vec_t vec_new(void);
struct vec_t vec_new_with_capacity(size_t cap);

enum result vec_set_val(struct vec_t *vec, size_t index, int64_t val);
enum result vec_append(struct vec_t *vec, int64_t val);
enum result vec_insert(struct vec_t *vec, size_t index, int64_t val);
enum result vec_pop(struct vec_t *vec, int64_t *out);
enum result vec_remove(struct vec_t *vec, size_t index, int64_t *out);
enum result vec_grow(struct vec_t *vec);
enum result
vec_shrink(struct vec_t *vec,
		   bool for_impending_len_incerease); // FIXME: Bad name, self pls fix
enum result vec_get_val(struct vec_t *vec, size_t index, int64_t *out);
bool vec_is_overly_large(struct vec_t *vec);
void vec_deinitialise(struct vec_t *vec);
#endif // LIST_VEC_H
