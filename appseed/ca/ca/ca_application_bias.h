#pragma once


namespace ca
{
   class application;
   class application_signal_object;
}


namespace ca
{


   // application_bias contains information inherited mainly and by-designly from calling party/application/system
   // for example, the OS command line can call a cube::system that takes a command line parameter that is
   // passed as application_bias to bergedge that can later pass or use this information as application_bias
   // for further actions.
   class CLASS_DECL_ca application_bias :
      virtual public ::ca::object
   {
   public:


      class CLASS_DECL_ca callback :
         virtual public ::ca::signalizable
      {
      public:


         void connect_to(::ca::application * papp);

         void on_call_signal(ca::signal_object * pobj);

         virtual void on_application_bias_callback_signal(::ca::application_signal_object * pobj);

      };

      
      ::user::interaction *      m_puiParent;
      callback *                 m_pcallback;
      ca::property_set          m_set;

      
      application_bias();
      application_bias(::ca::application * papp);
      application_bias(const application_bias & bias);
      application_bias & operator = (const application_bias & bias);

   };


   class CLASS_DECL_ca application_bias_sp :
      virtual public smart_pointer < application_bias >
   {
   public:


      application_bias_sp();
      application_bias_sp(::ca::application * papp);
      virtual ~application_bias_sp();


      using ::ca::smart_pointer < application_bias >::operator =;



   };


} // namespace ca