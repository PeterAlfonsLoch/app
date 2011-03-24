#include "StdAfx.h"

namespace mixer
{

   toggle_control::toggle_control(void) :
      control(new MixerCtrlDataSwitch())
   {
   }

   toggle_control::~toggle_control(void)
   {
   }

   MixerCtrlDataSwitch & toggle_control::get_data()
   {
      return *(MixerCtrlDataSwitch* ) m_pdata;
   }

} // namespace mixer