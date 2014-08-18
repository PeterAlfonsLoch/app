#pragma once


enum e_orientation
{

   orientation_none        = 0,
   orientation_horizontal  = 1,
   orientation_vertical    = 2,

};


#include "geometry_align.h"


#ifdef METROWIN
#include <intsafe.h>
#else
#ifndef LODWORD
#define LODWORD(l)           ((uint32_t)(((uint64_t)(l)) & 0xffffffff))
#endif
#ifndef HIDWORD
#define HIDWORD(l)           ((uint32_t)((((uint64_t)(l)) >> 32) & 0xffffffff))
#endif
#endif

#define MAKELONG64(a, b)      (((uint64_t)(((uint32_t)(((uint64_t)(a)) & 0xffffffff)) | ((uint64_t)((uint32_t)(((uint64_t)(b)) & 0xffffffff))) << 32)))

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int32_t)(int16_t)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int32_t)(int16_t)HIWORD(lp))
#endif

#define GET_X_LPARAM64(lp)                        ((int32_t)(int16_t)LODWORD(lp))
#define GET_Y_LPARAM64(lp)                        ((int32_t)(int16_t)HIDWORD(lp))



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

class CLASS_DECL_AXIS __point64
{
public:
    int64_t    x;
    int64_t    y;
};

typedef uchar      byte;
typedef uint16_t     uint16_t;
//typedef unsigned long      dword;
typedef uint64_t         qword;

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

class CLASS_DECL_AXIS __size64
{
public:
   int64_t     cx;
   int64_t     cy;
};

class CLASS_DECL_AXIS __rect64
{
public:
   int64_t     left;
   int64_t     top;
   int64_t     right;
   int64_t     bottom;
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






CLASS_DECL_AXIS int64_t MulDiv(int64_t nNumber, int64_t nNumerator, int64_t nDenominator);
CLASS_DECL_AXIS inline bool is64integer(int64_t i)
{
   return (i & 0xffffffff00000000 ) != 0;
}
CLASS_DECL_AXIS inline bool is64natural(uint64_t ui)
{
   return (ui & 0xffffffff00000000u ) != 0;
}
CLASS_DECL_AXIS inline bool is64integer(double d)
{
   return (d >= ((double) (int64_t) (0xfff0000000000000))) && (d < ((double) (uint64_t) 0xfffffffffffffu));
}
CLASS_DECL_AXIS inline bool is64natural(double d)
{
   return (d >= 0.0) && (d < ((double) (uint64_t) 0xfffffffffffffu));
}
CLASS_DECL_AXIS inline bool is32integer(double d)
{
   return (d >= ((double)(int64_t)(0xffffffff80000000LL))) && (d < ((double)(uint64_t)0x7fffffffu));
}
CLASS_DECL_AXIS inline bool is32natural(double d)
{
   return (d >= 0.0) && (d < ((double) (uint64_t) 0xffffffffu));
}
CLASS_DECL_AXIS inline bool is32integer(int64_t i)
{
   return (i >= (int64_t) 0xffffffff80000000LL) && (i <= 0x000000007fffffffLL);
}
CLASS_DECL_AXIS inline bool is32natural(int64_t i)
{
   return (i & 0xffffffff00000000 ) == 0;
}
CLASS_DECL_AXIS inline bool is32natural(uint64_t ui)
{
   return (ui & 0xffffffff00000000 ) == 0;
}
CLASS_DECL_AXIS inline bool is_double(int64_t i)
{
   if(i >= 0)
   {
      return (i & 0xfff0000000000000 ) != 0;
   }
   else
   {
      return (i & 0xffe0000000000000 ) != 0;
   }
}
CLASS_DECL_AXIS inline bool is_double(uint64_t ui)
{
   return (ui & 0xfff0000000000000 ) == 0;
}

CLASS_DECL_AXIS bool copy(__point64 * lpptDest,const POINT * lpptSrc);
CLASS_DECL_AXIS bool copy(LPPOINT lpptDest,const __point64 * lpptSrc);


CLASS_DECL_AXIS bool null(LPRECT prectDest);
CLASS_DECL_AXIS bool x_intersect_rect(LPRECT prect,LPCRECT prect1,LPCRECT prect2);
CLASS_DECL_AXIS bool y_intersect_rect(LPRECT prect,LPCRECT prect1,LPCRECT prect2);
CLASS_DECL_AXIS bool x_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_AXIS bool y_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_AXIS bool null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_AXIS bool x_left_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_AXIS bool y_top_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_AXIS bool top_left_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);


CLASS_DECL_AXIS bool copy(tagRECTD * prectDest, const tagRECTD * prectSrc);
CLASS_DECL_AXIS bool copy(tagRECTD * prectDest, const RECT * prectSrc);
CLASS_DECL_AXIS bool copy(RECT * prectDest, const tagRECTD * prectSrc);
CLASS_DECL_AXIS bool copy(tagRECTD * prectDest, const __rect64 * prectSrc);
CLASS_DECL_AXIS bool copy(__rect64 * prectDest, const tagRECTD * prectSrc);
CLASS_DECL_AXIS bool is_empty(const tagRECTD * prect);
CLASS_DECL_AXIS bool contains(const tagRECTD * prect, POINTD pt);
CLASS_DECL_AXIS bool set(tagRECTD * prectDest, double x1, double y1, double x2, double y2);
CLASS_DECL_AXIS bool null(tagRECTD * prectDest);
CLASS_DECL_AXIS bool is_equal(const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_AXIS bool inflate(tagRECTD * prect, double x, double y);
CLASS_DECL_AXIS bool deflate(tagRECTD * prect, double x, double y);
CLASS_DECL_AXIS bool offset(tagRECTD * prect, double x, double y);
CLASS_DECL_AXIS bool x_intersect_rect(tagRECTD * prect, const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_AXIS bool y_intersect_rect(tagRECTD * prect, const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_AXIS bool x_null_intersect_rect(tagRECTD * prect,const tagRECTD * prect1,const tagRECTD * prect2);
CLASS_DECL_AXIS bool y_null_intersect_rect(tagRECTD * prect,const tagRECTD * prect1,const tagRECTD * prect2);
CLASS_DECL_AXIS bool intersect(tagRECTD * prect,const tagRECTD * prect1,const tagRECTD * prect2);
CLASS_DECL_AXIS bool unite(tagRECTD * prect, const tagRECTD * prect1, const tagRECTD * prect2);
CLASS_DECL_AXIS double width(LPCRECTD lpcrect);
CLASS_DECL_AXIS double height(LPCRECTD lpcrect);
CLASS_DECL_AXIS double width(const RECTD & rect);
CLASS_DECL_AXIS double height(const RECTD & rect);

CLASS_DECL_AXIS bool copy(__rect64 * prectDest, const __rect64 * prectSrc);
CLASS_DECL_AXIS bool copy(__rect64 * prectDest, const RECT * prectSrc);
CLASS_DECL_AXIS bool copy(RECT * prectDest, const __rect64 * prectSrc);
CLASS_DECL_AXIS bool is_empty(const __rect64 * prect);
CLASS_DECL_AXIS bool contains(const __rect64 * prect, point64 pt);
CLASS_DECL_AXIS bool set(__rect64 * prectDest, int64_t x1, int64_t y1, int64_t x2, int64_t y2);
CLASS_DECL_AXIS bool null(__rect64 * prectDest);
CLASS_DECL_AXIS bool is_equal(const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_AXIS bool inflate(__rect64 * prect, int64_t x, int64_t y);
CLASS_DECL_AXIS bool deflate(__rect64 * prect, int64_t x, int64_t y);
CLASS_DECL_AXIS bool offset(__rect64 * prect, int64_t x, int64_t y);
CLASS_DECL_AXIS bool x_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_AXIS bool y_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_AXIS bool intersect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);
CLASS_DECL_AXIS bool unite(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2);


CLASS_DECL_AXIS bool deflate(LPRECT prect, const RECT & rect);






#include "geometry_types.h"




