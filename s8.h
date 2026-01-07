/*
 *
 */

#ifndef S8_H_
#define S8_H_

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

void s8_print(s8 s);
void s8_print_nl(s8 s);
s8 s8_buf(char buf[], size_t len);
void s8_free(s8 s);
s8 s8_null();
s8 s8_strcat(s8 prefix, s8 suffix);
int s8_strcmp(s8 s1, s8 s2);
s8 s8_strdup(s8 s);
size_t s8_strlen(s8 s);
s8 s8_strstr(s8 haystack, s8 needle);
s8 s8_strchr(s8 s, char c);
s8 s8_strtok(s8 *s, s8 delim);

#endif // S8_H_

#ifdef S8_IMPLEMENTATION
#include <stdlib.h>

struct _s8_strtok_state_t {
    size_t idx;
    s8 *s;
};

static struct _s8_strtok_state_t _s8_strtok_state = { 0 };

void s8_print(s8 s)
{
    printf(p_s8, S8_FMT(s));
}

void s8_print_nl(s8 s)
{
    printf(p_s8"\n", S8_FMT(s));
}

/* Create s8 from buffer. Dynamically allocates string.
 * Returns empty s8 on failure. */
s8 s8_buf(char buf[], size_t len)
{
    if (len == 0) return (s8) { 0 };

    size_t i = 0, j = 0;
    for (; i < len && buf[i]; i++) { }
    if (i == 0) return (s8) { 0 };

    char *str = malloc(i);
    if (!str) return (s8) { 0 };

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

s8 s8_null()
{
    return (s8) { 0 };
}

/* Creates s8 struct with concatenated prefix and suffix.
 * String is dynamically allocated.
 * Returns empty s8 on failure. */
s8 s8_strcat(s8 prefix, s8 suffix)
{
    char *str = malloc(prefix.len + suffix.len);
    if (!str) return (s8) { 0 };
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
    if (!str) return (s8) { 0 };
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
    return (s8) { 0 };
}

s8 s8_strchr(s8 s, char c)
{
    size_t i = 0;
    for (; i < s.len; i++) {
        if (s.str[i] == c) return (s8) {.len = s.len - i, .str = &s.str[i]};
    }
    return s8_null();
}

s8 s8_strtok(s8 *s, s8 delim)
{
    if (s) {
        _s8_strtok_state.s = s;
        _s8_strtok_state.idx = 0;
    }
    if (_s8_strtok_state.idx >= _s8_strtok_state.s->len) return s8_null();
    size_t start = _s8_strtok_state.idx;
    // loop through string to next delim
    for (; _s8_strtok_state.idx < _s8_strtok_state.s->len; _s8_strtok_state.idx++) {
        if (s8_strchr(delim, _s8_strtok_state.s->str[_s8_strtok_state.idx]).len) break;
    }
    size_t end = _s8_strtok_state.idx;
    // loop through rest of string to next non-delim
    for (; _s8_strtok_state.idx < _s8_strtok_state.s->len; _s8_strtok_state.idx++) {
        if (!s8_strchr(delim, _s8_strtok_state.s->str[_s8_strtok_state.idx]).len) break;
    }
    return (s8) {.len = end - start, .str = &_s8_strtok_state.s->str[start]};
}

#endif // S8_IMPLEMENTATION

#ifdef S8_STRIP_PREFIX

#define print s8_print
// #define buf s8_buf
// #define free s8_free
// #define null s8_null
#define strcat s8_strcat
#define strcmp s8_strcmp
#define strdup s8_strdup
#define strlen s8_strlen
#define strstr s8_strstr
#define strchr s8_strchr
#define strtok s8_strtok

#endif // S8_STRIP_PREFIX
