#include <stdlib.h>
#include <string.h>

#include "../defs.h"
#include "../log.h"
#include "vec.h"

struct vec_t vec_new(void) {
	// FIXME: clang-format is making this ugly, clang-format pls fix
	struct vec_t vec = {NULL, 0, 0};
	log_debug("vec initialised with cap, len 0");

	return vec;
}

enum result vec_pop(struct vec_t *vec, i64 *out) {

	// TODO: Look at this, I think we should punish users
	// for giving us nullptrs :^)
	if (vec == NULL) {
		return NULL_PTR;
	} else if (vec->len == 0) {
		return OK;
	}

	vec->len--;
	if (out != NULL) {
		*out = vec->buffer[vec->len];
	}

	/*
	 * I don't think we need this, because we can't read this data anyway
	 * therefore I think that it's just a waste of cpu time to clear the
	 * memory. Leaving it here in case I'm wrong.
	 * vec->buffer[vec->len] = 0;
	 */

	// Shrink vec if necessary
	if (vec_is_overly_large(vec)) {
		shrink_vec(vec);
	}
	return OK;
}

enum result vec_grow(struct vec_t *vec) {
	if (vec->cap == 0 || vec->buffer == NULL) {
		vec->cap = 1;
		i64 *buffer = xcalloc(vec->cap, 8);

		vec->buffer = buffer;
		return OK;
	}
	// Increase capacity and reallocate buffer
	vec->cap *= 2;
	log_trace("growing vec from capacity: %ld, to capacity: %ld", vec->cap / 2,
			  vec->cap);
	i64 *new_buffer = xrealloc(vec->buffer, vec->cap * 8);

	vec->buffer = new_buffer;
	return OK;
}
enum result vec_shrink(struct vec_t *vec) {
	log_trace("shrinking vec from capacity: %ld, to capacity: %ld", vec->cap,
			  vec->len);

	vec->cap = vec->len;
	i64 *new_buffer = xrealloc(vec->buffer, vec->cap * 8);

	vec->buffer = new_buffer;
	return OK;
}

struct vec_t vec_new_with_capacity(usize cap) {
	i64 *buffer = xcalloc(cap, 8);
	struct vec_t vec = {buffer, 0, cap};
	log_debug("vec initialised with size: %ld", cap);

	return vec;
}

enum result vec_remove(struct vec_t *vec, usize index, i64 *out) {
	if (vec == NULL) {
		return NULL_PTR; // TODO: Look at this, I think we should punish users
						 // for giving us nullptrs :^)
	} else if (index >= vec->len) {
		log_fatal("index %ld >= than length list of vec %ld", index, vec->len);
		exit(OUT_OF_BOUNDS);
	}

	log_trace("removing element: {%ld} from vec at index %ld",
			  vec->buffer[index], index);
	if (out != NULL) {
		*out = vec->buffer[index];
	}

	/*
	 * Carefully calculated idiocy ( I have the IQ of a brick wall ), preserved
	 * as a warning:
	 * ~~Carefully calculated genius ( I'm very humble )~~
	 * memmove(vec->buffer + (vec->len - (index + 1)),
	 * 			vec->buffer + (vec->len - index),
	 * 			(vec->len - (index + 1)) * sizeof(i64));
	 */

	// I don't think that we need this, as we can't access the data anyway
	// Left in just in case
	//	vec->buffer[index] = 0;

	// Move the elements forward
	memmove(vec->buffer + index, vec->buffer + (index + 1),
			(vec->len - (index + 1)) * sizeof(i64));
	vec->len--;

	if (vec_is_overly_large(vec)) {
		shrink_vec(vec);
	}
	return OK;
}

bool vec_is_overly_large(struct vec_t *vec) {
	return vec->len != 0 && vec->cap > vec->len * 2;
}
enum result vec_append(struct vec_t *vec, i64 val) {
	if (vec == NULL) {
		return NULL_PTR; // TODO: Look at this, I think we should punish users
						 // for giving us nullptrs :^)
	} else if (vec->cap < vec->len + 1) {
		vec_grow(vec);
	}
	vec->len++;
	vec->buffer[vec->len - 1] = val;
	if (vec_is_overly_large(vec)) {
		shrink_vec(vec);
	}
	return OK;
}

enum result vec_insert(struct vec_t *vec, usize index, i64 val) {
	if (vec == NULL) {
		return NULL_PTR; // TODO: Look at this, I think we should punish users
						 // for giving us nullptrs :^)
	} else if (index > vec->len) {
		log_error("index %ld greater than length of vec %ld", index, vec->len);
		exit(OUT_OF_BOUNDS);
	}
	if (vec->cap < vec->len + 1) {
		vec_grow(vec);
	}

	if (index == vec->len) {
		return vec_append(vec, val);
	}
	log_trace("moving data from i to i + 1");
	// Move all data within buffer to one index further on
	// 1. Say we have an array [1,2,3,4], insert '5' to index 2
	// 2. We need to move from 4 - 2 (2) to 2 + 1 (3)
	// 3. We need to move 4 - 2 elements
	//

	memmove(vec->buffer + index + 1, vec->buffer + index,
			(vec->len - index) * sizeof(i64));
	vec->len++;
	vec->buffer[index] = val;

	if (vec_is_overly_large(vec)) {
		shrink_vec(vec);
	}
	return OK;
}

enum result vec_set_val(struct vec_t *vec, usize index, i64 val) {
	if (index >= vec->len) {
		log_error("index %ld greater than length list of vec %ld", index,
				  vec->len);
		exit(OUT_OF_BOUNDS);
	}
	vec->buffer[index] = val;
	log_trace("setting value of vec at index %ld, as %ld", index, val);

	return OK;
}

// FIXME: I don't like using the out parameter
enum result vec_get_val(struct vec_t *vec, usize index, i64 *out) {
	if (index >= vec->len) {
		log_fatal("index %ld greater than length list of vec %ld", index,
				  vec->len);
		exit(OUT_OF_BOUNDS);
	}
	*out = vec->buffer[index];

	return OK;
}
// TODO: Should this be inlined???

enum result vec_print(struct vec_t *vec) {
	log_trace("starting to print vec");
	log_trace("printing first element");
	if (vec == NULL) {
		return NULL_PTR;
	} else if (vec->len == 0) {
		printf("[]");
		return OK;
	} else if (vec->len == 1) {
		printf("[%ld]", *vec->buffer);
		return OK;
	}

	printf("[%ld, ", vec->buffer[0]);
	for (usize i = 1; i < vec->len - 1; i++) {
		printf("%ld, ", vec->buffer[i]);
	}
	log_trace("printing last element");
	printf("%ld]\n", vec->buffer[vec->len - 1]);

	return OK;
}

void vec_deinitialise(struct vec_t *vec) { free(vec->buffer); }
