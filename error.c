#include "error.h"
#include "stdio.h"
#include "stdlib.h"

void check_alloc(void* pointer) {
	if (pointer == NULL) {
		fprintf(stderr, "Malloc error.");
		exit(EXIT_FAILURE);
	}
}
