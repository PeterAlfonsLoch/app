//
//  macos.h
//  ca
//
//  Created by Camilo Sasuke Tsumanuma on 1/28/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once

DWORD GetTickCount();

CLASS_DECL__ bool CopyRect(LPCRECT prectDest, LPCRECT prectSrc);
CLASS_DECL__ bool PtInRect(LPCRECT prect, POINT point);
CLASS_DECL__ bool SetRect(LPRECT prect, long x1, long y1, long x2, long y2);
CLASS_DECL__ bool SetRectEmpty(LPRECT prect);
CLASS_DECL__ bool EqualRect(LPCRECT prect1, LPCRECT prect2);
CLASS_DECL__ bool InflateRect(LPRECT prect, int x, int y);
CLASS_DECL__ bool OffsetRect(LPRECT prect, int x, int y);
CLASS_DECL__ bool IntersectRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL__ bool x_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL__ bool y_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL__ bool UnionRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);
CLASS_DECL__ bool SubtractRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2);


//typedef unsigned long * ULONG_PTR;

typedef unsigned long HRESULT;
//#define S_OK 0
//#define E_FAIL -1
//#define SUCCEEDED(hr) ((hr) >= 0)
//#define FAILED(hr) ((hr) < 0)


#define WINAPI



void RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const ULONG_PTR *lpArguments);
#define EXCEPTION_NONCONTINUABLE 1





namespace ex1
{
   
   
   class file;
   
   
} // namespace ex1


typedef ::ex1::file * HFILE;