#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//#define __FIB_DEV_UINT128
#define __FIB_DEV_BIGNUM

#ifdef __FIB_DEV_UINT128
#define BUF_SIZE 256
#elif defined(__FIB_DEV_BIGNUM)
#define BUF_SIZE 256
#else
#define BUF_SIZE 1
#endif

#define FIB_DEV "/dev/fibonacci"
int main()
{
    long long sz;

    char buf[BUF_SIZE];
    char write_buf[] = "testing writing";
    int offset = 200; /* TODO: try test something bigger than the limit */

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (int i = 0; i <= offset; i++) {
        sz = write(fd, write_buf, strlen(write_buf));
        printf("Writing to " FIB_DEV ", returned the sequence %lld\n", sz);
    }

    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        sz = read(fd, buf, sizeof(buf));

#if defined(__FIB_DEV_UINT128) || defined(__FIB_DEV_BIGNUM)
        buf[sz] = '\0';  // Add terminator
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%s.\n",
               i, buf);
#else
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%lld.\n",
               i, sz);
#endif
    }

    for (int i = offset; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        sz = read(fd, buf, sizeof(buf));
#if defined(__FIB_DEV_UINT128) || defined(__FIB_DEV_BIGNUM)
        buf[sz] = '\0';  // Add terminator
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%s.\n",
               i, buf);
#else
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%lld.\n",
               i, sz);
#endif
    }

    close(fd);
    return 0;
}
