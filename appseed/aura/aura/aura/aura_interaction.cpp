#include "framework.h"


namespace aura
{


   interaction::interaction()
   {
      
      m_pvoidUserInteraction = NULL;

   }


   interaction::~interaction()
   {


   }


   bool interaction::SetPlacement(const RECT & rect,UINT nFlags)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(nFlags);

      return false;

   }


} // namespace aura
























