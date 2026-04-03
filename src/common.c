#include <stdlib.h>

#include "common.h"

int str_cmp(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0') {
            return 0;
        }
    return *s1 - *s2;
}


int str_cat(char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return -1;
    for (; *s1; s1++)
        ;
    for (; (*s1 = *s2); s1++, s2++)
        ;
    return 1;
}
