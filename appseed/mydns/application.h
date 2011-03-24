#pragma once

namespace mydns
{
   class service;

   class CLASS_DECL_CA2_MYDNS application :
      public ::icube::application
   {
   public:


      mydns::service * m_pservice;


      application(void);
      virtual ~application(void);



      bool initialize_instance();
      virtual void netnode_run();
      virtual void on_request(var & varFile, var & varQuery);

      int CreateService();
      int RemoveService();

      virtual bool on_install();

      virtual int run();

   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace mydns