#include "framework.h"


device_context::device_context()
{


   m_pdisplay     = NULL;
   m_drawable     = None;
   m_gc           = None;
   m_pixmap       = None;
   m_window       = None;
   m_pt.x         = 0;
   m_pt.y         = 0;
   m_ptOffset.x   = 0;
   m_ptOffset.y   = 0;
   m_iScreen      = 0;
   m_iDepth       = 0;
   m_fontset      = None;



}



HDC CreateCompatibleDC(HDC hdcParam)
{

   HDC hdc = new device_context;

   return hdc;

}


WINBOOL ReleaseDC(oswindow hwnd, HDC hdc)
{


   single_lock sl(&user_mutex(), true);


   if(hdc == NULL)
      return FALSE;

   XFreeGC(hdc->m_pdisplay, hdc->m_gc);
   XCloseDisplay(hdc->m_pdisplay);

   delete hdc;
   return TRUE;

}







int32_t FillRect(HDC hdc, const RECT * lprc, HBRUSH hbr)
{

   single_lock sl(&user_mutex(), true);


   XFillRectangle(hdc->m_pdisplay, hdc->m_drawable, hdc->m_gc, lprc->left, lprc->top, lprc->right - lprc->left, lprc->bottom - lprc->top);
   return 1;
}




WINBOOL GetCursorPos(LPPOINT lpptCursor)
{

   //single_lock sl(user_mutex(), true);


   Window root_return;
   Window child_return;
   int32_t win_x_return;
   int32_t win_y_return;
   uint32_t mask_return;

   xdisplay display;

   display.open(NULL);

   if(display == NULL)
        return FALSE;

   XQueryPointer(display, display.default_root_window(), &root_return, &child_return, &lpptCursor->x, &lpptCursor->y, &win_x_return, &win_y_return, & mask_return);

   return TRUE;

}



WINBOOL SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT uFlags)
{

   single_lock sl(&user_mutex(), true);


   xdisplay display(hwnd->display());


   int32_t value_mask = 0;

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

   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter > 0)
   {
      value_mask |= CWSibling;
      values.sibling = hwndInsertAfter->window();
      values.stack_mode = Above;
   }

   if(uFlags & SWP_SHOWWINDOW)
   {
      XMapWindow(hwnd->display(), hwnd->window());
   }

   XConfigureWindow(hwnd->display(), hwnd->window(), value_mask, &values);


   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
   {
      if(hwndInsertAfter->window() == ZORDER_TOP || hwndInsertAfter->window() == ZORDER_TOPMOST)
      {
         XRaiseWindow(hwnd->display(), hwnd->window());
      }
      else if(hwndInsertAfter->window() == ZORDER_BOTTOM)
      {
         XLowerWindow(hwnd->display(), hwnd->window());
      }

   }

   //XCloseDisplay(display);

   return 1;

}



int32_t _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
{
   return 0;
}
