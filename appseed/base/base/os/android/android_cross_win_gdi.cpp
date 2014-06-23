#include "framework.h"

//
//
//device_context::device_context()
//{
//
//
//   m_pdc = NULL;
//
//
//
//}
//
//
//
//
//
//int_bool GetClientRect(oswindow hwnd, LPRECT lprect)
//{
//
//   synch_lock sl(&user_mutex());
//
////   XWindowAttributes attrs;
//
//   /* Fill attribute structure with information about root interaction_impl */
//
///*   if(XGetWindowAttributes(hwnd->display(), hwnd->interaction_impl(), &attrs) == 0)
//   {
//
//      return FALSE;
//
//   }
//
//   lprect->left      = 0;
//   lprect->top       = 0;
//   lprect->right     = lprect->left    + attrs.width;
//   lprect->bottom    = lprect->top     + attrs.height;
//   */
//
//   return TRUE;
//
//}
//
//
//int_bool GetWindowRect(oswindow hwnd, LPRECT lprect)
//{
//
//
//
//   synch_lock sl(&user_mutex());
//
//   if(!IsWindow(hwnd))
//      return FALSE;
//
//
//   bool bDestroying = hwnd->m_bDestroying;
///*   Display * pdisplay = hwnd->display();
//   Window interaction_impl = hwnd->interaction_impl();
//
//
//   if(pdisplay == NULL)
//    return FALSE;
//
//   XWindowAttributes attrs;
//
//
//   XSync(hwnd->display(), False);
//
//   // Fill attribute structure with information about root interaction_impl 
//
//   /*if(!XGetWindowAttributes(hwnd->display(), hwnd->interaction_impl(), &attrs))
//   {
//      return FALSE;
//   }
//
//   int x;
//   int y;
//   Window child;
//
//   if(!XTranslateCoordinates(hwnd->display(), hwnd->interaction_impl(), DefaultRootWindow(hwnd->display()), 0, 0, &x, &y, &child))
//   {
//      return FALSE;
//   }
//
//   lprect->left      = x;
//   lprect->top       = y;
//   lprect->right     = x    + attrs.width;
//   lprect->bottom    = y    + attrs.height;*/
//
//   return TRUE;
//
//}
//
//
//
//int32_t FillRect(HDC hdc, const RECT * lprc, HBRUSH hbr)
//{
//
//   synch_lock sl(&user_mutex());
//
//
//   //XFillRectangle(hdc->m_display, hdc->m_d, hdc->m_gc, lprc->left, lprc->top, lprc->right - lprc->left, lprc->bottom - lprc->top);
//   return 1;
//}
//
//
//
//int_bool GetCursorPos(LPPOINT lpptCursor)
//{
//
//   //synch_lock sl(&user_mutex());
//
//
//   Window root_return;
//   Window child_return;
//   int32_t win_x_return;
//   int32_t win_y_return;
//   uint32_t mask_return;
//
//   /*
//   xdisplay display;
//
//   display.open(NULL);
//
//   if(display == NULL)
//        return FALSE;
//
//   XQueryPointer(display, display.default_root_window(), &root_return, &child_return, &lpptCursor->x, &lpptCursor->y, &win_x_return, &win_y_return, & mask_return);
//   */
//
//   return TRUE;
//
//}
//
//
//
//int_bool SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT uFlags)
//{
//
//   synch_lock sl(&user_mutex());
//
//   /*
//   xdisplay display(hwnd->display());
//
//
//   int32_t value_mask = 0;
//
//   XWindowChanges values;
//
//   if(!(uFlags & SWP_NOMOVE))
//   {
//      value_mask |= CWX | CWY;
//      values.x = x;
//      values.y = y;
//   }
//
//   if(!(uFlags & SWP_NOSIZE))
//   {
//      value_mask |= CWWidth | CWHeight;
//      values.width = cx;
//      values.height = cy;
//   }
//
//   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter >= 0)
//   {
//      value_mask |= CWSibling;
//      values.sibling = hwndInsertAfter->interaction_impl();
//      values.stack_mode = Above;
//   }
//
//   XConfigureWindow(hwnd->display(), hwnd->interaction_impl(), value_mask, &values);
//
//   if(uFlags & SWP_SHOWWINDOW)
//   {
//      XMapWindow(hwnd->display(), hwnd->interaction_impl());
//   }
//
//   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
//   {
//      if(hwndInsertAfter->interaction_impl() == ZORDER_TOP || hwndInsertAfter->interaction_impl() == ZORDER_TOPMOST)
//      {
//         XRaiseWindow(hwnd->display(), hwnd->interaction_impl());
//      }
//      else if(hwndInsertAfter->interaction_impl() == ZORDER_BOTTOM)
//      {
//         XLowerWindow(hwnd->display(), hwnd->interaction_impl());
//      }
//
//   }
//
//   //XCloseDisplay(display);
//   */
//
//   return 1;
//
//}
//
//
///*
//int32_t _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
//{
//   return 0;
//}
//*/
//
//
//
