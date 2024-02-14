#ifndef __MY_BIGNUM_
#define __MY_BIGNUM_

#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#define MY_BIGNUM_MAX_LEN 54

#define INIT_STRING_LITERALS()           \
    (myBigN)                             \
    {                                    \
        .short_num = {.free_space = 15 } \
    }

#define MY_BIGNUM_TMP(x) myBigN_init(&INIT_STRING_LITERALS(), x)

/* The following structure is only for 64-bit architectures.
 *
 */

#define MY_BIGN_TMP()

typedef struct {
    char *ptr;
    size_t size : MY_BIGNUM_MAX_LEN, capcity : 6, is_ptr : 1, reserved : 3;
} myLong;

typedef struct {
    char data[15];
    uint8_t free_space : 4, reserved : 4;
} myShort;

typedef union {
    myLong long_num;
    myShort short_num;
} myBigN;

static inline bool myBigN_is_ptr(const myBigN *x)
{
    return x->long_num.is_ptr;
}
static inline size_t myBigN_capacity(const myBigN *x)
{
    return (myBigN_is_ptr(x)) ? ((size_t) 1 << (MY_BIGNUM_MAX_LEN)) - 1 : 15;
}
static inline size_t myBigN_size(const myBigN *x)
{
    return (myBigN_is_ptr(x)) ? x->long_num.size : 15 - x->short_num.free_space;
}

static inline char *myBigN_data(const myBigN *x)
{
    if (myBigN_is_ptr(x))
        return (char *) x->long_num.ptr;
    else
        return (char *) x->short_num.data;
}

myBigN *myBigN_setEmpty(myBigN *);
myBigN *myBigN_init(myBigN *, const char *);
myBigN *myBigN_free(myBigN *);
void myBigN_Add(myBigN *, const myBigN *, const myBigN *);
#endif