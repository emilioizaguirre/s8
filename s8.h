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

// usage: s8 str = S8_LIT("a string literal");
#define S8_LIT(s) (s8) {.len = sizeof((s)) - 1, .str = (char*) (s)}

// usage: printf("this is an s8 string: "p_s8"\n", S8_FMT(s));
#define S8_FMT(s) (int) (s).len, (s).str
#define p_s8 "%.*s"

/* declarations */
s8 s8_strstr(s8 haystack, s8 needle);
size_t s8_strlen(s8 s);
s8 s8_strdup(s8 s);
int s8_strcmp(s8 s1, s8 s2);
s8 s8_strcat(s8 prefix, s8 suffix);
void s8_free(s8 s);
s8 s8_buf(char buf[], size_t len);

/* implementations*/
/* Create s8 from buffer. Dynamically allocates string.
 * Returns empty s8 on failure. */
s8 s8_buf(char buf[], size_t len)
{
    if (len == 0) return (s8) {.len = 0, .str = NULL};

    size_t i = 0, j = 0;
    for (; i < len && buf[i]; i++) { }
    if (i == 0) return (s8) {.len = 0, .str = NULL};

    char *str = malloc(i);
    if (!str) return (s8) {.len = 0, .str = NULL};

    for (; j < i && buf[j]; j++) {
        str[j] = buf[j];
    }
    return (s8) {.len = j, .str = str};
}

/* Free dynamically allocated string in s8 struct. */
void s8_free(s8 s)
{
    free(s.str);
}

/* Creates s8 struct with concatenated prefix and suffix.
 * String is dynamically allocated.
 * Returns empty s8 on failure. */
s8 s8_strcat(s8 prefix, s8 suffix)
{
    char *str = malloc(prefix.len + suffix.len);
    if (!str) return (s8) {.len = 0, .str = NULL};
    for (size_t i = 0; i < prefix.len; i++) {
        str[i] = prefix.str[i];
    }
    for (size_t i = 0; i < suffix.len; i++) {
        str[i + prefix.len] = suffix.str[i];
    }
    return (s8) {.len = prefix.len + suffix.len, .str = str};
}

/* Compares two s8's.
 * Returns 0 if they're equal, <0 if s1 < s2, >0 if s1 > s2. */
int s8_strcmp(s8 s1, s8 s2)
{
    if (s1.len != s2.len) return s1.len - s2.len;
    size_t i = 0;
    for (; s1.str[i] == s2.str[i]; i++) {}
    return s1.str[i] - s2.str[i];
}

/* Create s8 from another s8. Dynamically allocates string.
 * Returns empty s8 on failure. */
s8 s8_strdup(s8 s)
{
    char *str = malloc(s.len);
    if (!str) return (s8) {.len = 0, .str = NULL};
    for (size_t i = 0; i < s.len; i++) {
        str[i] = s.str[i];
    }
    return (s8) {.len = s.len, .str = str};
}

/* Returns length of s8. */
size_t s8_strlen(s8 s)
{
    return s.len;
}

/* Returns s8 with substring view of needle in haystack if it is found,
 * empty s8 otherwise.*/
s8 s8_strstr(s8 haystack, s8 needle)
{
    size_t i, j = 0;
    for (i = 0; i < haystack.len; i++) {
        if (j == needle.len) break;
        if (haystack.str[i] == needle.str[j])   j++;
        else                            j = 0;
    }

    if (j == needle.len) return (s8) {.len = needle.len, .str = haystack.str + i - j};
    return (s8) {.len = 0, .str = NULL};
}
