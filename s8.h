/*
 *
 *
 *
 *
 *
 */

#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct s8_t s8;

struct s8_t {
    u64 len;
    u8 *str;
};

#define S8_LIT(s) (s8) {.len = sizeof((s)) - 1, .str = (u8*) (s)}
// the following allows printf(p_s8"\n", S8_FMT(s)); where s is s8 string.
#define S8_FMT(s) (int) (s).len, (s).str
#define p_s8 "%.*s"
