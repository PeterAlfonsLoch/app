#pragma once

namespace veievserver
{

   class CLASS_DECL_VEIEVSERVER application :
      public ::cube::application
   {
   public:


      veievserver::service * m_pservice;


      application(void);
      virtual ~application(void);



      bool initialize_instance();
      virtual void netnode_run();
      virtual void on_request(::ca::create_context * pcreatecontext);

      int CreateService();
      int RemoveService();

      virtual bool on_install();

      virtual int run();

   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace veievserver