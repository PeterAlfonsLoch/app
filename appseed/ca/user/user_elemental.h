#pragma once




namespace user
{

   class CLASS_DECL_ca elemental : 
      virtual public keyboard_focus,
      virtual public mouse_focus
   {
   public:

      virtual ::user::interaction * get_guie();
      virtual ::ca::graphics * _001GetDC();
      virtual void _001ReleaseDC(::ca::graphics * pdc);
      virtual void _001RedrawWindow();

      virtual void pre_translate_message(gen::signal_object * pobj);
   };

} // namespace user