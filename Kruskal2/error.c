#include "error.h"

#include "stdlib.h"
#include "stdio.h"

void error(char *code)
{
    printf("Erreur: %s", code);
    exit(EXIT_FAILURE);
}
