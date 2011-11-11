#pragma once

class MixerCtrlDataSwitch;

namespace mixer
{

   class CLASS_DECL_ca toggle_control :
      public control
   {
   public:
      toggle_control(void);

   public:
      virtual check::e_check _001GetCheck() = 0;
      virtual void _001SetCheck(check::e_check echeck) = 0;

      virtual void set_label(const char * lpcszLabel) = 0;

   public:
      virtual ~toggle_control(void);
      MixerCtrlDataSwitch & get_data();
   };


} // namespace mixer
