#pragma once


namespace user
{


   class CLASS_DECL_ca2 mouse_focus
   {
   public:
      mouse_focus();
      virtual ~mouse_focus();

      virtual void mouse_focus_OnLButtonUp(::ca2::signal_object * pobj);
   };


} // namespace user


