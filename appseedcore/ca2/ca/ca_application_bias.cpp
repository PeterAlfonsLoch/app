#include "StdAfx.h"


namespace ca
{


   application_bias::application_bias()
   {
   }

   application_bias::application_bias(const application_bias & bias)
   {
      operator = (bias);
   }
      
   application_bias & application_bias::operator = (const application_bias & bias)
   {
      if(this == &bias)
         return *this;
      m_strLicense         = bias.m_strLicense;
      return *this;
   }


} // namespace ca