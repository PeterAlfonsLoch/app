#pragma once




namespace user
{


   class CLASS_DECL_BASE elemental :
      virtual public keyboard_focus,
      virtual public mouse_focus
   {
   public:


      virtual void _001RedrawWindow();


      virtual void pre_translate_message(signal_details * pobj);


   };


} // namespace user




