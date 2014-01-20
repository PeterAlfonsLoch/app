#pragma once


namespace check
{


   typedef flags < e_check > check;


} // namespace check


namespace user
{


   class CLASS_DECL_BASE check_interface :
      virtual public ::object
   {
   public:


      virtual check::e_check _001GetCheck();
      virtual void _001SetCheck(bool b, ::action::context actioncontext);   // 0, 1
      virtual void _001SetCheck(check::e_check check, ::action::context actioncontext);
      virtual void _001ToggleCheck(::action::context actioncontext);


   };


} // namespace user


