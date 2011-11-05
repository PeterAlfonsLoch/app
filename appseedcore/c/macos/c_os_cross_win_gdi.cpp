#include "StdAfx.h"
#include "c_os_cross_win_gdi_internal.h"


HDC GetDC(HWND hwnd)
{

   HDC hdc = new device_context;

   hdc->m_display    = XOpenDisplay(NULL);
   hdc->m_hwnd       = hwnd;
   hdc->m_d          = (Drawable) (hwnd == NULL ? DefaultRootWindow(hdc->m_display) : hwnd);
   hdc->m_gc         = XCreateGC(hdc->m_display, hdc->m_d, 0, 0);

   return hdc;

}


HDC GetWindowDC(HWND hwnd)
{
   return GetDC(hwnd);
}


BOOL ReleaseDC(HWND hwnd, HDC hdc)
{

   if(hdc == NULL)
      return FALSE;

   XFreeGC(hdc->m_display, hdc->m_gc);
   XCloseDisplay(hdc->m_display);

   delete hdc;
   return TRUE;

}


BOOL GetClientRect(HWND hwnd, LPRECT lprect)
{
   XWindowAttributes attrs;
   /* Fill attribute structure with information about root window */
   if(XGetWindowAttributes(XOpenDisplay(NULL), hwnd, &attrs) == 0)
   {
      return false;
   }
   lprect->left      = 0;
   lprect->top       = 0;
   lprect->right     = lprect->left    + attrs.width;
   lprect->bottom    = lprect->top     + attrs.height;
}


BOOL GetWindowRect(HWND hwnd, LPRECT lprect)
{
   XWindowAttributes attrs;
   /* Fill attribute structure with information about root window */
   if(XGetWindowAttributes(XOpenDisplay(NULL), hwnd, &attrs) == 0)
   {
      return false;
   }
   lprect->left      = attrs.x;
   lprect->top       = attrs.y;
   lprect->right     = lprect->left    + attrs.width;
   lprect->bottom    = lprect->top     + attrs.height;
}



int FillRect(HDC hdc, const RECT * lprc, HBRUSH hbr)
{
   XFillRectangle(hdc->m_display, hdc->m_d, hdc->m_gc, lprc->left, lprc->top, lprc->right - lprc->left, lprc->bottom - lprc->top);
   return 1;
}


HDC BeginPaint(HWND hwnd, PAINTSTRUCT * ps)
{

   HDC hdc = GetDC(hwnd);

   GetClientRect(hwnd, &ps->rcPaint);

   return hdc;

}


BOOL EndPaint(HWND hwnd, PAINTSTRUCT * ps)
{

   return ReleaseDC(hwnd, ps->hdc);

}


BOOL GetCursorPos(LPPOINT lpptCursor)
{

   Window root_return;
   Window child_return;
   int win_x_return;
   int win_y_return;
   unsigned int mask_return;

   Display * display = XOpenDisplay(NULL);

   XQueryPointer(display, DefaultRootWindow(display), &root_return, &child_return, &lpptCursor->x, &lpptCursor->y, &win_x_return, &win_y_return, & mask_return);

   XCloseDisplay(display);

   return TRUE;

}



BOOL SetWindowPos(HWND hwnd, HWND hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{

   Display * display = XOpenDisplay(NULL);

   int value_mask = 0;

   XWindowChanges values;

   if(!(uFlags & SWP_NOMOVE))
   {
      value_mask |= CWX | CWY;
      values.x = x;
      values.y = y;
   }

   if(!(uFlags & SWP_NOSIZE))
   {
      value_mask |= CWWidth | CWHeight;
      values.width = cx;
      values.height = cy;
   }

   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter >= 0)
   {
      value_mask |= CWSibling;
      values.sibling = hwndInsertAfter;
      values.stack_mode = Above;
   }

   XConfigureWindow(display, hwnd, value_mask, &values);

   if(uFlags & SWP_SHOWWINDOW)
   {
      XMapWindow(display, hwnd);
   }

   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
   {
      if(hwndInsertAfter == ZORDER_TOP || hwndInsertAfter == ZORDER_TOPMOST)
      {
         XRaiseWindow(display, hwnd);
      }
      else if(hwndInsertAfter == ZORDER_BOTTOM)
      {
         XLowerWindow(display, hwnd);
      }

   }

   XCloseDisplay(display);

   return 1;

}



int _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
{
   return 0;
}




HFONT CreateFontIndirect(const LOGFONT * lf)
{
    return NULL;
}
HPEN CreatePen(int iPenStyle, int iWidth, COLORREF crColor)
{
    return NULL;
}
HGDIOBJ GetStockObject(int iStockObject)
{
    return NULL;
}
BOOL SelectObject(HDC hdc, HGDIOBJ hgdiobj)
{
    return FALSE;
}
BOOL Rectangle(HDC hdc, int x1, int y1, int x2, int y2)
{
    return FALSE;
}
BOOL DeleteObject(HGDIOBJ hgdiobj)
{
    return FALSE;
}
HDC CreateCompatibleDC(HDC hdc)
{
    return NULL;
}
HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset)
{
    return NULL;
}
BOOL SetTextColor(HDC hdc, COLORREF cr)
{
    return FALSE;
}
BOOL SetBkMode(HDC hdc, int iMode)
{
    return FALSE;
}
BOOL DeleteDC(HDC hdc)
{
    return FALSE;
}
BOOL AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn)
{
    return FALSE;
}
BOOL GetObject(HGDIOBJ hgdiobj, int iSize, void * object)
{
    return FALSE;
}
BOOL GetTextExtentPoint(HDC hdc, const char * pszText, int iSize, SIZE * psize)
{
    return FALSE;
}