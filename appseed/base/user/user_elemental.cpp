#include "framework.h"

namespace user
{

   sp(::user::interaction) elemental::get_guie()
   {
      return NULL;
   }

   ::draw2d::graphics * elemental::_001GetDC()
   {
      return get_guie()->GetDC();
   }

   void elemental::_001ReleaseDC(::draw2d::graphics * pdc)
   {
      get_guie()->ReleaseDC(pdc);
   }

   void elemental::_001RedrawWindow()
   {
   }

   void elemental::pre_translate_message(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

} // namespace user