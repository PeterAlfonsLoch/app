#pragma once


enum e_orientation
{

   orientation_none        = 0,
   orientation_horizontal  = 1,
   orientation_vertical    = 2,

};


#include "geometry_align.h"




struct SIZE64;
struct POINT64;
struct RECT64;
class size;
class size64;
class sized;
class point;
class point64;
class pointd;
class rect;
class rect64;
class rectd;

struct POINT64
{
    int64_t    x;
    int64_t    y;
};

typedef POINT64 * LPPOINT64;
typedef const POINT64 * LPCPOINT64;


typedef uchar      byte;
//typedef uint16_t     uint16_t;
//typedef unsigned long      dword;
//typedef uint64_t         qword;

struct POINT64;
struct SIZE64;
struct RECT64;
struct POINTD;
struct SIZED;
struct RECTD;

class size;
class size64;
class sized;
class point;
class point64;
class pointd;
class rect;
class rect64;
class rectd;

struct SIZE64
{
public:
   int64_t     cx;
   int64_t     cy;
};


typedef SIZE64 * LPSIZE64;
typedef const SIZE64 * LPCSIZE64;

struct RECT64
{
   int64_t     left;
   int64_t     top;
   int64_t     right;
   int64_t     bottom;
};

typedef RECT64 * LPRECT64;
typedef const RECT64 * LPCRECT64;


struct POINTD
{
    double  x;
    double  y;
};

typedef POINTD * LPPOINTD;
typedef const POINTD * LPCPOINTD;

struct SIZED
{
    double        cx;
    double        cy;
};

typedef SIZED * LPSIZED;
typedef const SIZED * LPCSIZED;

struct RECTD
{
    double  left;
    double  top;
    double  right;
    double  bottom;
};

typedef RECTD * LPRECTD;
typedef const RECTD * LPCRECTD;



struct Q4
{
public:


   double w;
   double x;
   double y;
   double z;


};




CLASS_DECL_ACE int64_t MulDiv(int64_t nNumber, int64_t nNumerator, int64_t nDenominator);
CLASS_DECL_ACE inline bool is64integer(int64_t i)
{
   return (i & 0xffffffff00000000 ) != 0;
}
CLASS_DECL_ACE inline bool is64natural(uint64_t ui)
{
   return (ui & 0xffffffff00000000u ) != 0;
}
CLASS_DECL_ACE inline bool is64integer(double d)
{
   return (d >= ((double) (int64_t) (0xfff0000000000000))) && (d < ((double) (uint64_t) 0xfffffffffffffu));
}
CLASS_DECL_ACE inline bool is64natural(double d)
{
   return (d >= 0.0) && (d < ((double) (uint64_t) 0xfffffffffffffu));
}
CLASS_DECL_ACE inline bool is32integer(double d)
{
   return (d >= ((double)(int64_t)(0xffffffff80000000LL))) && (d < ((double)(uint64_t)0x7fffffffu));
}
CLASS_DECL_ACE inline bool is32natural(double d)
{
   return (d >= 0.0) && (d < ((double) (uint64_t) 0xffffffffu));
}
CLASS_DECL_ACE inline bool is32integer(int64_t i)
{
   return (i >= (int64_t) 0xffffffff80000000LL) && (i <= 0x000000007fffffffLL);
}
CLASS_DECL_ACE inline bool is32natural(int64_t i)
{
   return (i & 0xffffffff00000000 ) == 0;
}
CLASS_DECL_ACE inline bool is32natural(uint64_t ui)
{
   return (ui & 0xffffffff00000000 ) == 0;
}
CLASS_DECL_ACE inline bool is_double(int64_t i)
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
CLASS_DECL_ACE inline bool is_double(uint64_t ui)
{
   return (ui & 0xfff0000000000000 ) == 0;
}

CLASS_DECL_ACE bool copy(POINT64 * lpptDest,const POINT * lpptSrc);
CLASS_DECL_ACE bool copy(LPPOINT lpptDest,const POINT64 * lpptSrc);


CLASS_DECL_ACE bool null(LPRECT prectDest);
CLASS_DECL_ACE bool x_intersect_rect(LPRECT prect,LPCRECT prect1,LPCRECT prect2);
CLASS_DECL_ACE bool y_intersect_rect(LPRECT prect,LPCRECT prect1,LPCRECT prect2);
CLASS_DECL_ACE bool x_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_ACE bool y_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_ACE bool null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_ACE bool x_left_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_ACE bool y_top_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);
CLASS_DECL_ACE bool top_left_null_intersect_rect(LPRECT lprect,LPCRECT lpcrect1,LPCRECT lpcrect2);


CLASS_DECL_ACE bool copy(RECTD * prectDest, const RECTD * prectSrc);
CLASS_DECL_ACE bool copy(RECTD * prectDest, const RECT * prectSrc);
CLASS_DECL_ACE bool copy(RECT * prectDest, const RECTD * prectSrc);
CLASS_DECL_ACE bool copy(RECTD * prectDest, const RECT64 * prectSrc);
CLASS_DECL_ACE bool copy(RECT64 * prectDest, const RECTD * prectSrc);
CLASS_DECL_ACE bool is_empty(const RECTD * prect);
CLASS_DECL_ACE bool contains(const RECTD * prect, POINTD pt);
CLASS_DECL_ACE bool set_rect(RECTD * prectDest, double x1, double y1, double x2, double y2);
CLASS_DECL_ACE bool null(RECTD * prectDest);
CLASS_DECL_ACE bool is_equal(const RECTD * prect1, const RECTD * prect2);
CLASS_DECL_ACE bool inflate(RECTD * prect, double x, double y);
CLASS_DECL_ACE bool deflate(RECTD * prect, double x, double y);
CLASS_DECL_ACE bool offset(RECTD * prect, double x, double y);
CLASS_DECL_ACE bool x_intersect_rect(RECTD * prect, const RECTD * prect1, const RECTD * prect2);
CLASS_DECL_ACE bool y_intersect_rect(RECTD * prect, const RECTD * prect1, const RECTD * prect2);
CLASS_DECL_ACE bool x_null_intersect_rect(RECTD * prect,const RECTD * prect1,const RECTD * prect2);
CLASS_DECL_ACE bool y_null_intersect_rect(RECTD * prect,const RECTD * prect1,const RECTD * prect2);
CLASS_DECL_ACE bool intersect(RECTD * prect,const RECTD * prect1,const RECTD * prect2);
CLASS_DECL_ACE bool unite(RECTD * prect, const RECTD * prect1, const RECTD * prect2);
CLASS_DECL_ACE double width(LPCRECTD lpcrect);
CLASS_DECL_ACE double height(LPCRECTD lpcrect);
CLASS_DECL_ACE double width(const RECTD & rect);
CLASS_DECL_ACE double height(const RECTD & rect);

CLASS_DECL_ACE bool copy(RECT64 * prectDest, const RECT64 * prectSrc);
CLASS_DECL_ACE bool copy(RECT64 * prectDest, const RECT * prectSrc);
CLASS_DECL_ACE bool copy(RECT * prectDest, const RECT64 * prectSrc);
CLASS_DECL_ACE bool is_empty(const RECT64 * prect);
CLASS_DECL_ACE bool contains(const RECT64 * prect, point64 pt);
CLASS_DECL_ACE bool set_rect(RECT64 * prectDest, int64_t x1, int64_t y1, int64_t x2, int64_t y2);
CLASS_DECL_ACE bool null(RECT64 * prectDest);
CLASS_DECL_ACE bool is_equal(const RECT64 * prect1, const RECT64 * prect2);
CLASS_DECL_ACE bool inflate(RECT64 * prect, int64_t x, int64_t y);
CLASS_DECL_ACE bool deflate(RECT64 * prect, int64_t x, int64_t y);
CLASS_DECL_ACE bool offset(RECT64 * prect, int64_t x, int64_t y);
CLASS_DECL_ACE bool resize(RECT64 * prect,int64_t cx,int64_t cy);
CLASS_DECL_ACE bool reverse_size(RECT64 * prect,int64_t cx,int64_t cy);
CLASS_DECL_ACE bool x_intersect_rect(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2);
CLASS_DECL_ACE bool y_intersect_rect(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2);
CLASS_DECL_ACE bool intersect(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2);
CLASS_DECL_ACE bool unite(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2);


CLASS_DECL_ACE bool deflate(LPRECT prect, const RECT & rect);



#include "geometry_point.h"
#include "geometry_size.h"
#include "geometry_rect.h"


#include "geometry_quaternions.h"


#include "geometry_types.h"




#include "geometry_size.inl"



