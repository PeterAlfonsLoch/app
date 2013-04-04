#include "framework.h"

namespace user
{

   ::user::interaction * elemental::get_guie()
   {
      return ::null();
   }

   ::ca::graphics * elemental::_001GetDC()
   {
      return get_guie()->GetDC();
   }

   void elemental::_001ReleaseDC(::ca::graphics * pdc)
   {
      get_guie()->ReleaseDC(pdc);
   }

   void elemental::_001RedrawWindow()
   {
   }

   void elemental::pre_translate_message(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

} // namespace user