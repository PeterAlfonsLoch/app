#pragma once

namespace mixeruserbase
{

   class CLASS_DECL_ca mute_control : 
      public simple_button,
      public mixer::toggle_control

   {
   public:
      mute_control(::ca::application * papp);
      virtual ~mute_control();

      virtual check::e_check _001GetCheck();
      virtual void _001SetCheck(check::e_check echeck);
      virtual void set_label(const char * lpcsz);

      virtual ::user::interaction * GetWnd();
      virtual bool Initialize(::user::interaction * pwndParent, UINT uiId);
      virtual int _GetDlgCtrlID();

   };

} // namespace mixeruserbase

