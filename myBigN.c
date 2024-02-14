#include "myBigN.h"
#include "__utility.h"
myBigN *myBigN_init(myBigN *x, const char *strNum)
{
    *x = INIT_STRING_LITERALS();
    //+ 1 for '\0'
    size_t len = strlen(strNum) + 1;
    if (len > 16) {
        x->long_num.size = len - 1;
        x->long_num.is_ptr = true;
        x->long_num.ptr = kmalloc(myBigN_size(x), GFP_KERNEL);
        memcpy(myBigN_data(x), strNum, len);

    } else {
        memcpy(x->short_num.data, strNum, len);
        x->short_num.free_space = 15 - len + 1;
    }

    return x;
}
myBigN *myBigN_setEmpty(myBigN *x)
{
    *x = INIT_STRING_LITERALS();
    return x;
}
myBigN *myBigN_free(myBigN *x)
{
    if (myBigN_is_ptr(x))
        kfree(x->long_num.ptr);
    x->long_num.is_ptr = false;
    return myBigN_setEmpty(x);
}

void myBigN_Add(myBigN *out, const myBigN *x, const myBigN *y)
{
    size_t sizeX = myBigN_size(x), sizeY = myBigN_size(y);
    char *dataX = myBigN_data(x), *dataY = myBigN_data(y);
    size_t i = 0;
    if (sizeX < sizeY) {
        __SWAP(dataX, dataY, char);
        __SWAP(&sizeX, &sizeY, size_t);
    }
    __reverse(dataX, sizeX);
    __reverse(dataY, sizeY);

    uint8_t carry = 0;
    char result[sizeX + 2];
    for (; i < sizeX || carry; i++) {
        uint8_t sum = ((i < sizeX) ? (dataX[i] - '0') : 0) +
                      ((i < sizeY) ? (dataY[i] - '0') : 0) + carry;
        result[i] = '0' + sum % 10;
        carry = sum / 10;
    }
    result[i] = 0;

    __reverse(result, i);
    __reverse(dataX, sizeX);
    __reverse(dataY, sizeY);
    if (out)
        *out = *MY_BIGNUM_TMP(result);
}