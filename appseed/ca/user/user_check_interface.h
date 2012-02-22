#pragma once


#include "gen/gen_flags.h"
#include "ca/primitive/check.h"


namespace check
{


   typedef flags < e_check > check;


} // namespace check


namespace user
{


   class CLASS_DECL_ca check_interface :
      virtual public ::radix::object
   {
   public:


      virtual check::e_check _001GetCheck();
      virtual void _001SetCheck(bool b = true, bool bUser = true);   // 0, 1
      virtual void _001SetCheck(check::e_check check, bool bUser);
      virtual void _001ToggleCheck(bool bUser);


   };


} // namespace user


