#include <stdio.h>
#include "s8.h"

int main(void)
{
    s8 test = S8_LIT("hello world");
    printf("this is a s8 string: \""p_s8"\" it has length %ld\n", S8_FMT(test), test.len);
    return 0;
}
