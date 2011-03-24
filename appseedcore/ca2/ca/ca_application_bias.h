#pragma once


namespace ca
{

   // application_bias contains information inherited mainly and by-designly from calling party/application/system
   // for example, the OS command line can call a icube::system that takes a command line parameter that is
   // passed as application_bias to bergedge that can later pass or use this information as application_bias
   // for further actions.
   class CLASS_DECL_ca application_bias
   {
   public:
      
      
      string   m_strLicense;

      
      application_bias();
      application_bias(const application_bias & bias);
      application_bias & operator = (const application_bias & bias);

   };

} // namespace ca