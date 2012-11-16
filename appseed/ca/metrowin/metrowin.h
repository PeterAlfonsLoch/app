#pragma once


CLASS_DECL_ca bool CopyRect(LPCRECT prectDest, LPCRECT prectSrc);
CLASS_DECL_ca bool PtInRect(LPCRECT prect, POINT point);
CLASS_DECL_ca bool SetRect(LPRECT prect, long x1, long y1, long x2, long y2);
CLASS_DECL_ca bool SetRectEmpty(LPRECT prect);
CLASS_DECL_ca bool EqualRect(LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca bool InflateRect(LPRECT prect, int x, int y);
CLASS_DECL_ca bool OffsetRect(LPRECT prect, int x, int y);
CLASS_DECL_ca bool IntersectRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca bool x_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca bool y_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca bool UnionRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca bool SubtractRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);



//#define WINAPI



//void RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const ulong_ptr *lpArguments);


namespace ex1
{


   class file;


} // namespace ex1


//typedef ::ex1::file * HFILE;



//#include "os_allocate_debug.h"
//#include "os_debug.h"


//CLASS_DECL_ca errno_t fopen_s(FILE ** pFile, const char * pFileName, const char * mode);

//#include "os_multithreading.h"
