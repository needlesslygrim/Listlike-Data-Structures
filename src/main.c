#include <stdint.h>
#include <stdio.h>

#include "log.h"
#include "vec/vec.h"

int main() {
	log_set_level(LOG_ERROR);
	struct vec_t vec = vec_new_with_capacity(3);
	vec_set_val(&vec, 0, 2);
	vec_set_val(&vec, 1, 3);
	vec_set_val(&vec, 2, 4);
	int64_t out;
	vec_get_val(&vec, 1, &out);
	vec_append(&vec, 10);
	vec_insert(&vec, 3, 11);
	int64_t val = -5;
	vec_get_val(&vec, vec.len - 1, &val);
	printf("%ld\n", val);
	vec_deinitialise(&vec);
}
