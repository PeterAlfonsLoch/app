#pragma once

namespace tesseract
{

   namespace simpledb
   {

      class CLASS_DECL_CA2_TESSERACT application :
         virtual public ::tesseract::mail::application
      {
      public:


         bool                          m_bServer;

         ::simpledb::service *         m_pservice;
         ::simpledb::manager *         m_pmanager;



         application();


         virtual bool initialize_instance();
         virtual int exit_instance();

         virtual void on_request(::ca::create_context * pcreatecontext);

         virtual void simpledb_run();
         virtual BOOL run();

         int CreateService();
         int RemoveService();

      };


      inline application & app_cast(::ca::application * papp)
      {
         return *dynamic_cast < application * > (papp);
      }

   } // namespace simpledb


} // namespace tesseract


