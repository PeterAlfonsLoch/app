#pragma once


namespace netshareservercfg
{


   class CLASS_DECL_CA2_NETSHARESERVERCFG application :
      public ::cube::application
   {
   public:


      configuration * m_pconfiguration;


      application(void);
      virtual ~application(void);


      virtual bool initialize_instance();
      virtual int exit_instance();

   
      virtual void on_request(::ca::create_context * pcreatecontext);


   };


} // namespace netshareservercfg


