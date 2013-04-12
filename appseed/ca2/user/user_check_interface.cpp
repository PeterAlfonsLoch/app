#include "framework.h"

namespace user
{

   check::e_check check_interface::_001GetCheck()
   {
      return check::unchecked;
   }

   void check_interface::_001SetCheck(bool bChecked, bool bUser)
   {
      _001SetCheck((check::e_check) (bChecked ? check::checked : check::unchecked), bUser);
   }

   void check_interface::_001SetCheck(check::e_check echeck, bool bUser)
   {
      UNREFERENCED_PARAMETER(echeck);
      UNREFERENCED_PARAMETER(bUser);
   }

   void check_interface::_001ToggleCheck(bool bUser)
   {
      if(_001GetCheck() == check::checked)
      {
         _001SetCheck(check::unchecked, bUser);
      }
      else if(_001GetCheck() == check::unchecked)
      {
         _001SetCheck(check::checked, bUser);
      }
      else if(_001GetCheck() == check::tristate)
      {
         _001SetCheck(check::unchecked, bUser);
      }
      else
      {
         _001SetCheck(check::unchecked, bUser);
      }
   }

} // namespace user