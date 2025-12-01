#ifndef _INC_DSA_ERRNO_
#define _INC_DSA_ERRNO_

#include <stdint.h>

typedef enum {
    DSA_NO_ERR = 0,
    DSA_OUT_OF_MEM,
} DSA_ERRNO_ENUM;

typedef uint8_t dsa_errno_t;

#endif