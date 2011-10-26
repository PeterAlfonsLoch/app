#include "StdAfx.h"


namespace ca
{

   void application_bias::callback::connect_to(::ca::application * papp)
   {
      set_app(papp);
      (dynamic_cast < ::radix::application * > (m_papp))->m_signal.connect(this, &callback::on_call_signal);
   }

   void application_bias::callback::on_call_signal(gen::signal_object * pobj)
   {
      SCAST_PTR(::radix::application_signal_object, papplicationsignal, pobj);
      on_application_bias_callback_signal(papplicationsignal);
   }

   void application_bias::callback::on_application_bias_callback_signal(::radix::application_signal_object * papplicationsignal)
   {
      UNREFERENCED_PARAMETER(papplicationsignal);
   }


   application_bias::application_bias()
   {
      m_set["SessionSynchronizedInput"]      = true;
      m_set["NativeWindowFocus"]             = true;
      m_puiParent                            = NULL;
   }

   application_bias::application_bias(::ca::application * papp) :
      ca(papp)
   {
      m_set["SessionSynchronizedInput"]      = true;
      m_set["NativeWindowFocus"]             = true;
      m_puiParent                            = NULL;
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
      m_puiParent          = bias.m_puiParent;
      m_set                = bias.m_set;
      return *this;
   }


   application_bias_sp::application_bias_sp()
   {
   }

   application_bias_sp::application_bias_sp(::ca::application * papp) :
      ca(papp),
      ::ca::smart_pointer < application_bias > (papp)
   {
   }

   application_bias_sp::~application_bias_sp()
   {
   }


} // namespace ca