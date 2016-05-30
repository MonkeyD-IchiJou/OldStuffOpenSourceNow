#ifndef UTIL_H
#define UTIL_H

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ZERO_MEM(a) memset(a, 0, sizeof(a))

#define EPSILON  0.0001f  //Used for error checking
#define	PI  3.1415926535897932384626433832795f
#define TWO_PI  PI * 2.0f
#define HALF_PI  PI / 2.0f
#define QUARTER_PI  PI / 4.0f




#endif
