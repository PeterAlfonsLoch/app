#include "StdAfx.h"

namespace mixer
{

control::control(MixerCtrlData * pdata)
{
   m_pdata = pdata;
}

control::~control(void)
{
   if(m_pdata != NULL)
   {
      delete m_pdata;
      m_pdata = NULL;
   }
}

} // namespace mixer