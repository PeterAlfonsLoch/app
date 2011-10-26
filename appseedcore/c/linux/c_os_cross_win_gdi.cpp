#include "StdAfx.h"


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
   int mask_return;

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
