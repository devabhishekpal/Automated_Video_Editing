#ifndef _UTIL_API_
#define _UTIL_API_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

char *catVars(char **dest, int num, ...);

bool safeRealloc(char** data, size_t size);

char *printVars(int num, ...);

void clearStr(char* str, int num);

#endif