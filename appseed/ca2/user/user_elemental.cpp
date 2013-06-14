#include "framework.h"

namespace user
{

   sp(::user::interaction) elemental::get_guie()
   {
      return NULL;
   }

   ::ca2::graphics * elemental::_001GetDC()
   {
      return get_guie()->GetDC();
   }

   void elemental::_001ReleaseDC(::ca2::graphics * pdc)
   {
      get_guie()->ReleaseDC(pdc);
   }

   void elemental::_001RedrawWindow()
   {
   }

   void elemental::pre_translate_message(::ca2::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

} // namespace user