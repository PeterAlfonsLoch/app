#pragma once

namespace user
{


   class CLASS_DECL_ca mouse_focus
   {
   public:
      mouse_focus();
      virtual ~mouse_focus();

      virtual void mouse_focus_OnLButtonUp(gen::signal_object * pobj);
   };


} // namespace user