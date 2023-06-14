#ifndef DEFS_H
#define DEFS_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define signed integer types
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Define unsigned integer types
typedef uint8_t u8;
typedef int16_t u16;
typedef int32_t u32;
typedef uint64_t u64;

// Define architecture-specific sized types
typedef size_t usize;

// A clever hack from SerenityOS :^):
// https://awesomekling.github.io/How-SerenityOS-declares-ssize_t/
#define unsigned signed
typedef __SIZE_TYPE__ isize;
#undef unsigned

// Helper functions, as in this scenario we don't care about what happens
// when memory is used up. Thank you glibc documentation :^)
static void *xmalloc(usize size) {
	void *buffer = malloc(size);
	if (buffer == NULL) {
		fprintf(stderr, "fatal error: memory exhausted");
		exit(1);
	}

	return buffer;
}

static void *xcalloc(usize count, usize eltsize) {
	void *buffer = calloc(count, eltsize);
	if (buffer == NULL) {
		fprintf(stderr, "fatal error: memory exhausted");
		exit(1);
	}

	return buffer;
}

static void *xrealloc(void *ptr, usize size) {
	void *buffer = realloc(ptr, size);
	if (buffer == 0) {
		fprintf(stderr, "fatal error: memory exhausted");
		exit(1);
	}

	return buffer;
}

// Assert that can be enabled with conditional compilation
// Credit: Beej's C Programming Guide, Chapter: The C Preprocessor
#if ASSERT_ENABLED
#define assert(condition, message)                                             \
	do {                                                                       \
		if (!(condition)) {                                                    \
			fprintf(stderr, __FILE__ ":%d: assertion %s failed: %s\n",         \
					__LINE__, #condition, message);                            \
			exit(1);                                                           \
		}                                                                      \
	} while (0)
#else
#define assert(c, m) // Empty macro if not enabled
#endif
#endif // DEFS_H
