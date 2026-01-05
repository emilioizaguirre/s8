#include <stdio.h>
#include <unistd.h>
#define S8_IMPLEMENTATION
#include "s8.h"

int main(void)
{
    s8 test = S8_LIT("hello world");
    printf("this is a s8 string: \""p_s8"\" it has length %ld\n", S8_FMT(test), test.len);

    char buf[10] = { 0 };
    ssize_t res = read(STDIN_FILENO, buf, 10);
    if (res == -1) return 1;
    s8 user_s = s8_buf(buf, 10);
    if (user_s.len == 0) return -1;
    printf("this is a s8 string: \""p_s8"\" it has length %ld\n", S8_FMT(user_s), user_s.len);
    s8_free(user_s);

    s8 string_to_find_chars = S8_LIT("some chars 1234");
    s8 find_s = s8_strchr(string_to_find_chars, 's');
    s8_print_nl(find_s);
    printf("%ld\n", find_s.len);
    s8 find_1 = s8_strchr(string_to_find_chars, '1');
    s8_print_nl(find_1);
    printf("%ld\n", find_1.len);
    s8 find_r = s8_strchr(string_to_find_chars, 'r');
    s8_print_nl(find_r);
    printf("%ld\n", find_r.len);
    s8 find_p = s8_strchr(string_to_find_chars, 'p');
    s8_print_nl(find_p);
    printf("%ld\n", find_p.len);

    s8 string_to_tokenize = S8_LIT("what the, hell is, going on in there");
    s8 delim = S8_LIT(", ");
    for (s8 t = s8_strtok(&string_to_tokenize, delim); t.len; t = s8_strtok(NULL, delim)) {
        printf("%ld: ", t.len);
        s8_print_nl(t);
    }

    return 0;
}
