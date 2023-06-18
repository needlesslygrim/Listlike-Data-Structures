#include <stdio.h>

#define ASSERT_ENABLED 1

#include <defs.h>
#include "log.h"
#include <vec.h>

int main() {
	log_set_level(LOG_DEBUG);
	struct vec_t vec = vec_new();
	vec_grow_to(&vec, 3414);
	for (usize i = 0; i < 3414; i++) {
		vec_append(&vec, 3);
	}
	vec_deinitialise(&vec);
}
