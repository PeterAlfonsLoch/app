#pragma once


namespace user
{


   class CLASS_DECL_BASE mouse_focus
   {
   public:
      mouse_focus();
      virtual ~mouse_focus();

      virtual void mouse_focus_OnLButtonUp(signal_details * pobj);
   };


} // namespace user


