#pragma once


// application_bias contains information inherited mainly and by-designly from calling party/application/system
// for example, the OS command line can call a cube::system that takes a command line parameter that is
// passed as application_bias to bergedge that can later pass or use this information as application_bias
// for further actions.
class CLASS_DECL_AXIS application_bias :
   virtual public ::object
{
public:


   class CLASS_DECL_AXIS callback :
      virtual public signalizable
   {
   public:


      void connect_to(sp(::axis::application) papp);

      void on_call_signal(signal_details * pobj);

      virtual void on_application_bias_callback_signal(::axis::application_signal_details * pobj);

   };


   ::user::interaction *      m_puiParent;
   callback *                 m_pcallback;
   property_set               m_set;


   application_bias();
   application_bias(sp(::axis::application) papp);
   application_bias(const application_bias & bias);
   application_bias & operator = (const application_bias & bias);

};







