#include <stdio.h>

#define ASSERT_ENABLED 1

#include "defs.h"
#include "log.h"
#include "vec/vec.h"

int main() {
	log_set_level(LOG_DEBUG);
	struct vec_t vec = vec_new();
	for (i32 i = 0; i < 100; i++) {
		vec_append(&vec, i + 1);
	}
	for (int i = 0; i < 50; i++) {
		vec_pop(&vec, NULL);
	}
	vec_print(&vec);
	vec_deinitialise(&vec);
}
