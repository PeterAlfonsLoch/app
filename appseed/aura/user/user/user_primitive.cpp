#include "framework.h"


namespace user
{


   primitive::primitive()
   {

      m_pvoidUserInteraction = NULL;

   }


   primitive::~primitive()
   {


   }


#ifdef WINDOWSEX


   bool primitive::GetWindowPlacement(WINDOWPLACEMENT * lpwndpl)
   {

      UNREFERENCED_PARAMETER(lpwndpl);

      return false;

   }

   bool primitive::SetWindowPlacement(const WINDOWPLACEMENT * lpcwndpl)
   {

      UNREFERENCED_PARAMETER(lpcwndpl);

      return false;

   }


#endif // WINDOWSEX


   bool primitive::SetPlacement(const RECT & rect,UINT nFlags)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(nFlags);

      return false;

   }

   int32_t primitive::get_total_page_count(::job * pjob)
   {
      UNREFERENCED_PARAMETER(pjob);
      return 1;
   }



   void primitive::_001OnTimer(::timer * ptimer)
   {

      UNREFERENCED_PARAMETER(ptimer);

   }


} // namespace user
























