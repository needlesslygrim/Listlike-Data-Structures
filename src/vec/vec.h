//
// Created by erickth on 24/05/23.
//

#ifndef LIST_VEC_H
#define LIST_VEC_H

#include <stddef.h>
#include <stdlib.h>

struct vec_t {
	int64_t *data;
	size_t len;
};

enum result {
	OUT_OF_BOUNDS,
	OK
};

struct vec_t vec_new(void);
struct vec_t vec_new_with_capacity(size_t len);

enum result vec_set_val(struct vec_t *vec, int64_t val, size_t index);
enum result vec_get_val(struct vec_t *vec, size_t index, int64_t *out);

void vec_deinitialise(struct vec_t *vec);
#endif // LIST_VEC_H
