#include <stdlib.h>
#include <string.h>

#include <log.h>
#include <defs.h>
#include <vec.h>

struct vec_t vec_new(void) {
	// FIXME: clang-format is making this ugly, clang-format pls fix
	struct vec_t vec = {NULL, 0, 0};
	log_debug("vec initialised with cap, len 0");

	return vec;
}

struct vec_t vec_new_with_capacity(usize cap) {
	assert(cap != 0, "cannot initialise a vec using `vec_new_with_capacity()` "
					 "with capacity == 0");
	i64 *buffer = xcalloc(cap, 8);
	struct vec_t vec = {buffer, 0, cap};
	log_debug("vec initialised with size: %ld", cap);

	return vec;
}

void vec_set_at(struct vec_t *vec, usize index, i64 val) {
	assert(vec != NULL, "null pointer passed to `vec_set_val()`");
	assert(index < vec->len, "index %ld >= than length of vec %ld, in `vec_set_at()`", index, vec->len);

	log_trace("setting value of vec at index %ld, as %ld", index, val);
	vec->buffer[index] = val;
}

void vec_get_at(struct vec_t *vec, usize index, i64 *out) {
	assert(vec != NULL, "null pointer passed to `vec_set_val()` as `vec`");
	assert(out != NULL, "null pointer passed to `vec_set_val()` as `out`");
	assert(index < vec->len, "index %ld >= than length of vec %ld, in `vec_get_at()`", index, vec->len);

	*out = vec->buffer[index];
}

void vec_append(struct vec_t *vec, i64 val) {
	assert(vec != NULL, "null pointer passed to `vec_append()`");

	if (vec->cap < vec->len + 1) {
		vec_grow(vec);
	}
	vec->len++;
	vec->buffer[vec->len - 1] = val;
	if (vec_is_overly_large(vec)) {
		vec_shrink(vec);
	}
}

void vec_insert(struct vec_t *vec, usize index, i64 val) {
	assert(vec != NULL, "null pointer passed to `vec_insert()`");
	assert(index <= vec->len, "index %ld > than length of vec %ld in `vec_insert()`", index,
		   vec->len);

	if (vec->cap < vec->len + 1) {
		vec_grow(vec);
	}

	if (index == vec->len) {
		vec_append(vec, val);
		return;
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
		vec_shrink(vec);
	}
}

void vec_pop(struct vec_t *vec, i64 *out) {
	assert(vec != NULL, "null pointer passed to `vec_pop()`");
	if (vec->len == 0) {
		return;
	}

	if (out != NULL) {
		*out = vec->buffer[vec->len];
	}

	vec->len--;

	/*
	 * I don't think we need this, because we can't read this data anyway
	 * therefore I think that it's just a waste of cpu time to clear the
	 * memory. Leaving it here in case I'm wrong.
	 * vec->buffer[vec->len] = 0;
	 */

	// Shrink vec if necessary
	if (vec_is_overly_large(vec)) {
		vec_shrink(vec);
	}
}

void vec_remove(struct vec_t *vec, usize index, i64 *out) {
	assert(vec != NULL, "null pointer passed to `vec_remove()`");
	assert(index >= vec->len, "index %ld >= than length of vec %ld in `vec_remove()`", index,
		   vec->len);

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
		vec_shrink(vec);
	}
}

void vec_grow(struct vec_t *vec) {
	assert(vec != NULL, "null pointer passed to `vec_grow()`");

	if (vec->cap == 0 || vec->buffer == NULL) {
		vec->cap = 1;
		vec->buffer = xcalloc(vec->cap, 8);
		return;
	}
	// Increase capacity and reallocate buffer
	vec->cap *= 2;
	log_trace("growing vec from capacity: %ld, to capacity: %ld", vec->cap / 2,
			  vec->cap);
	vec->buffer = xrealloc(vec->buffer, vec->cap * 8);
}

void vec_grow_to(struct vec_t *vec, usize cap) {
	assert(vec != NULL, "null pointer passed to `vec_grow_to()`");

	assert(cap != 0, "cannot grow vec to size 0 in `vec_grow_to()`");
	assert(
		cap >= vec->cap,
		"cannot grow vec to cap (%ld) <= existing cap (%ld) in `vec_grow_to()`",
		cap, vec->cap);
	vec->cap = cap;
	vec->buffer = xrealloc(vec->buffer, cap * 8);
}

void vec_shrink(struct vec_t *vec) {
	assert(vec != NULL, "null pointer passed to `vec_shrink()`");
	assert(vec->len != 0, "vec length cannot be equal to zero when shrinking a "
						  "vec in `vec_grow()`");

	log_trace("shrinking vec from capacity: %ld, to capacity: %ld", vec->cap,
			  vec->len);

	vec->cap = vec->len;
	vec->buffer = xrealloc(vec->buffer, vec->cap * 8);;
}

bool vec_is_overly_large(struct vec_t *vec) {
	assert(vec != NULL, "null pointer passed to `vec_is_overly_large()`");
	return vec->len != 0 && vec->cap > vec->len * 2;
}

void vec_print(struct vec_t *vec) {
	assert(vec != NULL, "null pointer passed to `vec_print()`");

	log_trace("starting to print vec");
	log_trace("printing first element");
	if (vec->len == 0) {
		printf("[]");
		return;
	} else if (vec->len == 1) {
		printf("[%ld]", *vec->buffer);
		return;
	}

	printf("[%ld, ", vec->buffer[0]);
	for (usize i = 1; i < vec->len - 1; i++) {
		printf("%ld, ", vec->buffer[i]);
	}
	log_trace("printing last element");
	printf("%ld]\n", vec->buffer[vec->len - 1]);
}

void vec_deinitialise(struct vec_t *vec) {
	assert(vec != NULL, "null pointer passed to `vec_deinitialise()`");
	if (vec->buffer == NULL) { return; }

	free(vec->buffer);
	vec->buffer = NULL;
}
