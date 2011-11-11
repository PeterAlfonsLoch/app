#include "StdAfx.h"

namespace mixer
{

   label::label(void) :
      control(new MixerCtrlData)
   {
   }

   label::~label(void)
   {
   }

   MixerCtrlData & label::get_data()
   {
      return *(MixerCtrlData* ) m_pdata;
   }



} // namespace mixer