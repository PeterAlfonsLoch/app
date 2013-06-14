#include "framework.h"



namespace ca2
{


   void application_bias::callback::connect_to(sp(::ca2::application) papp)
   {
      set_app(papp);
      m_papp.cast < application >()->m_psignal->connect(this, &callback::on_call_signal);
   }

   void application_bias::callback::on_call_signal(::ca2::signal_object * pobj)
   {
      SCAST_PTR(::ca2::application_signal_object, papplicationsignal, pobj);
      on_application_bias_callback_signal(papplicationsignal);
   }

   void application_bias::callback::on_application_bias_callback_signal(::ca2::application_signal_object * papplicationsignal)
   {
      UNREFERENCED_PARAMETER(papplicationsignal);
   }


   application_bias::application_bias()
   {
      m_set["SessionSynchronizedInput"]      = true;
      m_set["NativeWindowFocus"]             = true;
      m_puiParent                            = NULL;
   }

   application_bias::application_bias(sp(::ca2::application) papp) :
      ca2(papp)
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


} // namespace ca2
