#pragma once




namespace user
{

   class CLASS_DECL_ca2 elemental : 
      virtual public keyboard_focus,
      virtual public mouse_focus
   {
   public:

      virtual sp(::user::interaction) get_guie();
      virtual ::ca2::graphics * _001GetDC();
      virtual void _001ReleaseDC(::ca2::graphics * pdc);
      virtual void _001RedrawWindow();

      virtual void pre_translate_message(::ca2::signal_object * pobj);
   };

} // namespace user