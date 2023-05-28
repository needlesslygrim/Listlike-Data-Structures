#include <bits/time.h>
#include <stdlib.h>
#include <string.h>

#include "../log.h"

#include "vec.h"

struct vec_t vec_new(void) {
	// FIXME: clang-format is making this ugly, clang-format pls fix
	struct vec_t vec = {calloc(0, 8), 0, 0};
	log_debug("vec initialised with cap, len 0");

	return vec;
}

struct vec_t vec_new_with_capacity(size_t cap) {
	struct vec_t vec = {calloc(cap, 8), 0, cap};
	log_debug("vec initialised with size: %ld", cap);

	return vec;
}

enum result vec_grow(struct vec_t *vec) {
	// Increase capacity and reallocate buffer
	vec->cap *=
		2; // TODO: Investigate other factors, perhaps square the current cap?
	log_debug("growing vec from capacity: %ld, to capacity: %ld", vec->cap / 2,
			  vec->cap);
	int64_t *new_data = realloc(vec->data, vec->cap * 8);
	if (new_data == NULL) {
		log_error("error growing vec to len: %ld", vec->cap);
		return RESIZE_FAILURE;
	}
	vec->data = new_data;
	return OK;
}

enum result vec_shrink(struct vec_t *vec, bool for_impending_len_increase) {
	log_debug("shrinking vec from capacity: %ld, to capacity: %ld", vec->cap,
			  vec->len + (for_impending_len_increase ? 1 : 0));

	vec->cap = vec->len + (for_impending_len_increase
							   ? 1
							   : 0); // TODO: think about whether this is bad
	int64_t *new_data = realloc(vec->data, vec->cap * 8);
	if (new_data == NULL) {
		log_error("error shrinking vec to len: %ld", vec->cap);
		return RESIZE_FAILURE;
	}
	vec->data = new_data;
	return OK;
}

bool vec_is_overly_large(struct vec_t *vec) {
	// FIXME: Look at other ways of determining if it is overly large
	return vec->len != 0 && vec->cap > vec->len * 3;
}
enum result vec_append(struct vec_t *vec, int64_t val) {
	if (vec->cap < vec->len + 1) {
		vec_grow(vec);
	} else if (vec_is_overly_large(vec)) {
		vec_shrink(vec, true);
		// TODO: See if there is a better way than doing this on every append,
		// maybe every five appends?
	}
	vec->len++;
	vec->data[vec->len - 1] = val;

	return OK;
}

enum result vec_insert(struct vec_t *vec, size_t index, int64_t val) {
	if (vec->cap < vec->len + 1) {
		vec_grow(vec);
	} else if (vec_is_overly_large(vec)) {
		vec_shrink(vec, true);
	}
	if (index == vec->len) {
		return vec_append(vec, val);
	}
	log_trace("moving data from i to i + 1");
	// Move all data within buffer to one index further on
	memmove(vec->data + 1, vec->data, vec->len < index ? vec->len : vec->len - index);
	vec->len++;
	vec->data[index] = val;

	return OK;
}

enum result vec_set_val(struct vec_t *vec, size_t index, int64_t val) {
	if (index >= vec->len) {
		log_error("index %ld greater than length list of vec %ld", index,
				  vec->len);
		return OUT_OF_BOUNDS;
	}
	vec->data[index] = val;
	log_trace("setting value of vec at index %ld, as %ld", index, val);

	return OK;
}

// FIXME: I don't like using the out parameter
enum result vec_get_val(struct vec_t *vec, size_t index, int64_t *out) {
	if (index >= vec->len) {
		log_fatal("index %ld greater than length list of vec %ld", index,
				  vec->len);
		return OUT_OF_BOUNDS;
	}
	*out = vec->data[index];

	return OK;
}
// TODO: Should this be inlined???
inline void vec_deinitialise(struct vec_t *vec) {
	log_debug("deinitialising vec");
	free(vec->data);
}
