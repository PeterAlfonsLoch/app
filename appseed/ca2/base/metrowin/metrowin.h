#pragma once


CLASS_DECL_ca2 DWORD GetTickCount();


/*CLASS_DECL_ca2 bool CopyRect(LPRECT prectDest, LPCRECT prectSrc);
CLASS_DECL_ca2 bool PtInRect(LPCRECT prect, POINT point);
CLASS_DECL_ca2 bool SetRect(LPRECT prect, long x1, long y1, long x2, long y2);
CLASS_DECL_ca2 bool SetRectEmpty(LPRECT prect);
CLASS_DECL_ca2 bool EqualRect(LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca2 bool InflateRect(LPRECT prect, int x, int y);
CLASS_DECL_ca2 bool OffsetRect(LPRECT prect, int x, int y);
CLASS_DECL_ca2 bool IntersectRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca2 bool x_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca2 bool y_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca2 bool UnionRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL_ca2 bool SubtractRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
*/


//#define WINAPI



//void RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const ulong_ptr *lpArguments);


namespace ex1
{


   class file;


} // namespace ex1


//typedef ::ca::file * HFILE;



//#include "os_allocate_debug.h"
//#include "os_debug.h"


//CLASS_DECL_ca2 errno_t fopen_s(FILE ** pFile, const char * pFileName, const char * mode);

//#include "os_multithreading.h"




CLASS_DECL_ca2 BOOL WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam);

#define PostMessage PostMessageW



