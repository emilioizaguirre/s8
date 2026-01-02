/*
 *
 *
 *
 *
 *
 */

#include <stdlib.h>

typedef struct s8_t s8;

struct s8_t {
    size_t len;
    char *str;
};

#define S8_LIT(s) (s8) {.len = sizeof((s)) - 1, .str = (char*) (s)}
#define S8_FMT(s) (int) (s).len, (s).str
#define p_s8 "%.*s"

s8 s8_buf(char buf[], size_t len)
{
    size_t i;
    for (i = 0; buf[i]; i++) { }
    char *str = malloc(i);
    if (!str) return (s8) {.len = 0, .str = NULL};
    for (size_t j = 0; j < i; j++) {
        str[j] = buf[j];
    }
    return (s8) {.len = len, .str = str};
}

void s8_free(s8 s)
{
    free(s.str);
}
