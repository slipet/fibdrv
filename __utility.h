#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#define __SWAP(a, b, type) \
    do {                   \
        type *_a = (a);    \
        type *_b = (b);    \
        *(_a) ^= *(_b);    \
        *(_b) ^= *(_a);    \
        *(_a) ^= *(_b);    \
    } while (0)
void __reverse(char *, ssize_t);

#endif