//#include "framework.h"



void application_bias::callback::connect_to(::aura::application * papp)
{
   set_app(papp);
   m_pauraapp->m_psignal->connect(this, &callback::on_call_signal);
}

void application_bias::callback::on_call_signal(signal_details * pobj)
{
   SCAST_PTR(::aura::application_signal_details, papplicationsignal, pobj);
   on_application_bias_callback_signal(papplicationsignal);
}

void application_bias::callback::on_application_bias_callback_signal(::aura::application_signal_details * papplicationsignal)
{
   UNREFERENCED_PARAMETER(papplicationsignal);
}


application_bias::application_bias()
{
   m_set["SessionSynchronizedInput"]      = true;
   m_set["NativeWindowFocus"]             = true;
   m_puiParent                            = NULL;
}

application_bias::application_bias(::aura::application * papp) :
   object(papp)
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

   m_puiParent          = bias.m_puiParent;
   m_set                = bias.m_set;

   return *this;

}




