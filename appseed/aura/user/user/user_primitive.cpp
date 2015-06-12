#include "framework.h"


namespace user
{


   elemental::elemental()
   {

      m_pvoidUserInteraction = NULL;

   }


   elemental::~elemental()
   {


   }


#ifdef WINDOWSEX


   bool elemental::GetWindowPlacement(WINDOWPLACEMENT * lpwndpl)
   {

      UNREFERENCED_PARAMETER(lpwndpl);

      return false;

   }

   bool elemental::SetWindowPlacement(const WINDOWPLACEMENT * lpcwndpl)
   {

      UNREFERENCED_PARAMETER(lpcwndpl);

      return false;

   }


#endif // WINDOWSEX


   bool elemental::SetPlacement(const RECT & rect,UINT nFlags)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(nFlags);

      return false;

   }


} // namespace aura
























