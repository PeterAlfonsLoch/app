//#include "framework.h"


namespace aura
{


   interaction::interaction()
   {
      
      m_pvoidUserInteraction = NULL;

   }


   interaction::~interaction()
   {


   }


#ifdef WINDOWSEX


   bool interaction::GetWindowPlacement(WINDOWPLACEMENT * lpwndpl)
   {

      UNREFERENCED_PARAMETER(lpwndpl);

      return false;

   }

   bool interaction::SetWindowPlacement(const WINDOWPLACEMENT * lpcwndpl)
   {

      UNREFERENCED_PARAMETER(lpcwndpl);

      return false;

   }


#endif // WINDOWSEX


   bool interaction::SetPlacement(const RECT & rect,UINT nFlags)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(nFlags);

      return false;

   }


} // namespace aura
























