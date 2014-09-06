#include "framework.h" // previously aura/user/user.h


namespace user
{


   check::e_check check_interface::_001GetCheck()
   {

      return check::unchecked;

   }


   void check_interface::_001SetCheck(bool bChecked,::action::context actioncontext)
   {

      _001SetCheck((check::e_check) (bChecked ? check::checked : check::unchecked),actioncontext);

   }


   void check_interface::_001SetCheck(check::e_check echeck,::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(echeck);
      UNREFERENCED_PARAMETER(actioncontext);

   }


   void check_interface::_001ToggleCheck(::action::context actioncontext)
   {

      if(_001GetCheck() == check::checked)
      {

         _001SetCheck(check::unchecked,actioncontext);

      }
      else if(_001GetCheck() == check::unchecked)
      {

         _001SetCheck(check::checked,actioncontext);

      }
      else if(_001GetCheck() == check::tristate)
      {

         _001SetCheck(check::unchecked,actioncontext);

      }
      else
      {

         _001SetCheck(check::unchecked,actioncontext);

      }

   }


} // namespace user






