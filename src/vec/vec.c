#include "vec.h"

struct vec_t vec_new(void) {

	struct vec_t vec = {calloc(0, 8), 0};
	return vec;
}

struct vec_t vec_new_with_capacity(size_t len) {
	struct vec_t vec = {calloc(len, 8), len};

	return vec;
}

enum result vec_set_val(struct vec_t *vec, int64_t val, size_t index) {
	if (index >= vec->len) { return OUT_OF_BOUNDS; }
	vec->data[index] = val;
	return OK;
}

enum result vec_get_val(struct vec_t *vec, size_t index, int64_t *out) {
	if (index >= vec->len) { return OUT_OF_BOUNDS; }
	*out = vec->data[index];
	return OK;
}

void vec_deinitialise(struct vec_t *vec) { free(vec->data); }