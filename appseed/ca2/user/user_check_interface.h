#pragma once


#include "base/ca2/ca_flags.h"



namespace check
{


   typedef flags < e_check > check;


} // namespace check


namespace user
{


   class CLASS_DECL_ca2 check_interface :
      virtual public ::ca2::object
   {
   public:


      virtual check::e_check _001GetCheck();
      virtual void _001SetCheck(bool b = true, bool bUser = true);   // 0, 1
      virtual void _001SetCheck(check::e_check check, bool bUser);
      virtual void _001ToggleCheck(bool bUser);


   };


} // namespace user


