#include <stdio.h>
#include <unistd.h>
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
    return 0;
}
