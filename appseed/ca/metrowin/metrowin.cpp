#include "framework.h"


#ifdef METROWIN
[Platform::MTAThread]
#endif
extern "C" int APIENTRY
DllMain( HINSTANCE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                )
{
    switch (ul_reason_for_call)
   {
      case DLL_PROCESS_ATTACH:
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
         break;
    }
    return TRUE;
}


DWORD GetTickCount()
{
    return GetTickCount64() % 0xffffffffULL;
}


CLASS_DECL_ca bool CopyRect(LPRECT prectDest, LPCRECT prectSrc)
{
      prectDest->left = prectSrc->left;
      prectDest->top = prectSrc->top;
      prectDest->right = prectSrc->right;
      prectDest->bottom = prectSrc->bottom;
   return true;
}

CLASS_DECL_ca bool PtInRect(LPCRECT prect, POINT point)
{
   return point.x >= prect->left && point.x <= prect->right
   && point.y >= prect->top && point.y <= prect->bottom;

}

CLASS_DECL_ca bool SetRect(LPRECT prect, long x1, long y1, long x2, long y2)
{

   prect->left = x1;
   prect->top = y1;

   prect->right = x2;
   prect->bottom = y2;
   return true;
}


CLASS_DECL_ca bool SetRectEmpty(LPRECT prect)
{

   SetRect(prect, 0, 0, 0, 0);
   return true;
}


CLASS_DECL_ca bool EqualRect(LPCRECT prect1, LPCRECT prect2)
{
      return prect1->left == prect2->left
         &&  prect1->top == prect2->top
         &&  prect1->right == prect2->right
         &&  prect1->bottom == prect2->bottom;
}


CLASS_DECL_ca bool InflateRect(LPRECT prect, int x, int y)
{
      prect->left -= x;
      prect->top -= y;
      prect->right += x;
      prect->bottom += y;
      return true;
}

CLASS_DECL_ca bool OffsetRect(LPRECT prect, int x, int y)
{
      prect->left += x;
      prect->top += y;
      prect->right += x;
      prect->bottom += y;
      return true;
}

CLASS_DECL_ca bool x_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->left = max(prect1->left, prect2->left);
   prect->right = min(prect1->right, prect2->right);
   return prect->right >= prect->left;
}

CLASS_DECL_ca bool y_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->top = max(prect1->top, prect2->top);
   prect->right = min(prect1->bottom, prect2->bottom);
   return prect->bottom >= prect->top;
}

CLASS_DECL_ca bool IntersectRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   bool bXIntersects = x_intersect_rect(prect, prect1, prect2);
   bool bYIntersects = y_intersect_rect(prect, prect1, prect2);
   return bXIntersects && bYIntersects;
}


CLASS_DECL_ca bool UnionRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->left = min(prect1->left, prect2->left);
   prect->top = min(prect1->top, prect2->top);
   prect->right = max(prect1->right, prect2->right);
   prect->bottom = max(prect1->bottom, prect2->bottom);
   return ((prect->right - prect->left) > 0) && ((prect->bottom - prect->top) > 0);
}


CLASS_DECL_ca bool SubtractRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   RECT rect;
   bool bXIntersects = x_intersect_rect(&rect, prect1, prect2);
   bool bYIntersects = y_intersect_rect(&rect, prect1, prect2);
   if(bXIntersects)
   {
      prect->left    = rect.left;
      prect->right   = rect.right;
   }
   if(bYIntersects)
   {
      prect->top    = rect.top;
      prect->bottom   = rect.bottom;
   }
   return bXIntersects || bYIntersects;
}



/*
CLASS_DECL_ca errno_t fopen_s(FILE ** pFile, const char * pFileName, const char * mode)
{
   if(pFile == NULL)
   {
      return EINVAL;
   }

   *pFile = fopen(pFileName, mode);

   if(*pFile == NULL)
   {
      return errno;
   }

   return 0;

}
*/





CLASS_DECL_ca BOOL WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   if(oswindow.window() == NULL || oswindow.window()->m_pthread == NULL)
      return FALSE;

   HANDLE h = oswindow.window()->m_pthread->get_os_data();

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   mutex_lock ml(pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.oswindow   = oswindow;
   msg.message    = Msg;
   msg.wParam     = wParam;
   msg.lParam     = lParam;

   pmq->ma.add(msg);
   
   pmq->m_eventNewMessage.set_event();

   return true;

}
