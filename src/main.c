#include <stdint.h>
#include <stdio.h>

#include "vec/vec.h"

int main() {
	struct vec_t vec = vec_new_with_capacity(3);
	vec_set_val(&vec, 2, 0);
	vec_set_val(&vec, 3, 1);
	int64_t out;
	vec_get_val(&vec, 1, &out);
	printf("%d", out);
	vec_deinitialise(&vec);
}
