#pragma once

#include "muldiv64.h"
#include "align.h"

#define MAKELONG64(a, b)      (((uint64_t)(((unsigned int)(((uint64_t)(a)) & 0xffffffff)) | ((uint64_t)((unsigned int)(((uint64_t)(b)) & 0xffffffff))) << 32)))
#define LODWORD(l)           ((unsigned int)(((uint64_t)(l)) & 0xffffffff))
#define HIDWORD(l)           ((unsigned int)((((uint64_t)(l)) >> 32) & 0xffffffff))


#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif

#define GET_X_LPARAM64(lp)                        ((int)(short)LODWORD(lp))
#define GET_Y_LPARAM64(lp)                        ((int)(short)HIDWORD(lp))



class __size64;
class size;
class size64;
class __point64;
class point;
class point64;
class __rect64;
class rect;
class rect64;

class CLASS_DECL__ __point64
{
public:
    __int64    x;
    __int64    y;
};

typedef unsigned char      byte;
typedef unsigned short     word;
typedef unsigned long      dword;
typedef __uint64_t         qword;
typedef unsigned int       uint;

class __size64;
class size;
class size64;
class __point64;
class point;
class point64;
class __rect64;
class rect;
class rect64;

class CLASS_DECL__ __size64
{
public:
   __int64     cx;
   __int64     cy;
};

class CLASS_DECL__ __rect64
{
public:
   __int64     left;
   __int64     top;
   __int64     right;
   __int64     bottom;
};




#include "size.h"
#include "point.h"
#include "rectangle.h"


CLASS_DECL__ __int64 MulDiv(__int64 nNumber, __int64 nNumerator, __int64 nDenominator);
CLASS_DECL__ inline bool is64(__int64 i)
{
   return (i & 0xffffffff00000000 ) != 0;
}
CLASS_DECL__ bool copy(__rect64 * prectDest, const __rect64 * prectSrc);
CLASS_DECL__ bool copy(__rect64 * prectDest, const RECT * prectSrc);
CLASS_DECL__ bool copy(RECT * prectDest, const __rect64 * prectSrc);
CLASS_DECL__ bool is_empty(const __rect64 * prect);
CLASS_DECL__ bool contains(const __rect64 * prect, point64 pt);
CLASS_DECL__ bool set(__rect64 * prectDest, __int64 x1, __int64 y1, __int64 x2, __int64 y2);
CLASS_DECL__ bool null(__rect64 * prectDest);
CLASS_DECL__ bool is_equal(const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL__ bool inflate(__rect64 * prect, __int64 x, __int64 y);
CLASS_DECL__ bool deflate(__rect64 * prect, __int64 x, __int64 y);
CLASS_DECL__ bool offset(__rect64 * prect, __int64 x, __int64 y);
CLASS_DECL__ bool x_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL__ bool y_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL__ bool intersect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL__ bool unite(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL__ long width(LPRECT lpcrect);
CLASS_DECL__ long height(LPCRECT lpcrect);


CLASS_DECL__ bool deflate(LPRECT prect, LPCRECT lpcrect);