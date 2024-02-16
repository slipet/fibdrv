#include "__utility.h"


void __reverse(char *str, ssize_t len)
{
    int l = 0, r = len - 1;
    while (l < r) {
        __SWAP((str + l), (str + r), char);
        l++;
        r--;
    }
}
