#pragma once

#include "api/muldiv64.h"
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
class sized;
class __point64;
class point;
class point64;
class pointd;
class __rect64;
class rect;
class rect64;
class rectd;

class CLASS_DECL_ca __point64
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
typedef DWORD_PTR          dwordptr;

class __size64;
class size;
class size64;
struct tagSIZED;
class sized;
class __point64;
class point;
class point64;
struct tagPOINTD;
class pointd;
class __rect64;
class rect;
class rect64;
struct tagRECTD;
class rectd;

class CLASS_DECL_ca __size64
{
public:
   __int64     cx;
   __int64     cy;
};

class CLASS_DECL_ca __rect64
{
public:
   __int64     left;
   __int64     top;
   __int64     right;
   __int64     bottom;
};


typedef struct tagPOINTD
{
    double  x;
    double  y;
} POINTD, *PPOINTD, NEAR *NPPOINTD, FAR *LPPOINTD;

typedef struct tagSIZED
{
    double        cx;
    double        cy;
} SIZED, *PSIZED, *LPSIZED;

typedef struct tagRECTD
{
    double  left;
    double  top;
    double  right;
    double  bottom;
} RECTD, *PRECTD, NEAR *NPRECTD, FAR *LPRECTD;

typedef const RECTD FAR* LPCRECTD;




#include "size.h"
#include "point.h"
#include "rectangle.h"


CLASS_DECL_ca __int64 MulDiv(__int64 nNumber, __int64 nNumerator, __int64 nDenominator);
CLASS_DECL_ca inline bool is64(__int64 i)
{
   return (i & 0xffffffff00000000 ) != 0;
}
CLASS_DECL_ca bool copy(tagRECTD * prectDest, const tagRECTD * prectSrc);
CLASS_DECL_ca bool copy(tagRECTD * prectDest, const RECT * prectSrc);
CLASS_DECL_ca bool copy(RECT * prectDest, const tagRECTD * prectSrc);
CLASS_DECL_ca bool copy(tagRECTD * prectDest, const __rect64 * prectSrc);
CLASS_DECL_ca bool copy(__rect64 * prectDest, const tagRECTD * prectSrc);
CLASS_DECL_ca bool is_empty(const tagRECTD * prect);
CLASS_DECL_ca bool contains(const tagRECTD * prect, POINTD pt);
CLASS_DECL_ca bool set(tagRECTD * prectDest, double x1, double y1, double x2, double y2);
CLASS_DECL_ca bool null(tagRECTD * prectDest);
CLASS_DECL_ca bool is_equal(const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_ca bool inflate(tagRECTD * prect, double x, double y);
CLASS_DECL_ca bool deflate(tagRECTD * prect, double x, double y);
CLASS_DECL_ca bool offset(tagRECTD * prect, double x, double y);
CLASS_DECL_ca bool x_intersect_rect(tagRECTD * prect, const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_ca bool y_intersect_rect(tagRECTD * prect, const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_ca bool intersect(tagRECTD * prect, const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_ca bool unite(tagRECTD * prect, const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_ca double width(LPRECTD lpcrect);
CLASS_DECL_ca double height(LPCRECTD lpcrect);

CLASS_DECL_ca bool copy(__rect64 * prectDest, const __rect64 * prectSrc);
CLASS_DECL_ca bool copy(__rect64 * prectDest, const RECT * prectSrc);
CLASS_DECL_ca bool copy(RECT * prectDest, const __rect64 * prectSrc);
CLASS_DECL_ca bool is_empty(const __rect64 * prect);
CLASS_DECL_ca bool contains(const __rect64 * prect, point64 pt);
CLASS_DECL_ca bool set(__rect64 * prectDest, __int64 x1, __int64 y1, __int64 x2, __int64 y2);
CLASS_DECL_ca bool null(__rect64 * prectDest);
CLASS_DECL_ca bool is_equal(const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_ca bool inflate(__rect64 * prect, __int64 x, __int64 y);
CLASS_DECL_ca bool deflate(__rect64 * prect, __int64 x, __int64 y);
CLASS_DECL_ca bool offset(__rect64 * prect, __int64 x, __int64 y);
CLASS_DECL_ca bool x_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_ca bool y_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_ca bool intersect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_ca bool unite(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);

CLASS_DECL_ca long width(LPRECT lpcrect);
CLASS_DECL_ca long height(LPCRECT lpcrect);


CLASS_DECL_ca bool deflate(LPRECT prect, LPCRECT lpcrect);
