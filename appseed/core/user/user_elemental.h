#pragma once




namespace user
{

   class CLASS_DECL_ca2 elemental : 
      virtual public keyboard_focus,
      virtual public mouse_focus
   {
   public:

      virtual sp(::user::interaction) get_guie();
      virtual ::draw2d::graphics * _001GetDC();
      virtual void _001ReleaseDC(::draw2d::graphics * pdc);
      virtual void _001RedrawWindow();

      virtual void pre_translate_message(signal_details * pobj);
   };

} // namespace user