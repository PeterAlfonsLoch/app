#include "framework.h"


namespace dynamic_source
{


   script_interface::script_interface()
   {

      if(get_app() != NULL)
      {
         m_spmemoryfileFallback = canew(::http::memory_file(get_app()));
      }
      
      m_pinstanceMain      = NULL;
      m_pinstanceParent    = NULL;
      m_pnetnodesocket     = NULL;
      m_pmanager           = NULL;

      m_pscript            = NULL;

      
      m_iDebug             = 0;

   }

   script_interface::~script_interface()
   {
   }

   void script_interface::destroy()
   {
   }


   void script_interface::run()
   {
      

   }

   void script_interface::dinit()
   {
   }

   void script_interface::dprint(const char *)
   {
   }


   ::ca::property & script_interface::get(const char * pszKey)
   {
      return oprop(pszKey);
   }


   bool script_interface::main_initialize()
   {

      return true;

   }

   bool script_interface::main_finalize()
   {
      m_pnetnodesocket     .release();
      m_pmanager           .release();

      m_pscript            .release();
      m_pinstanceMain      .release();
      m_pinstanceParent    .release();

      return true;

   }

   ::http::file & script_interface::output_file()
   {
      if(m_pinstanceMain == this)
      {
         return *((::http::file *) NULL);
      }
      else if(m_pinstanceMain != NULL)
      {
         return m_pinstanceMain->output_file();
      }
      else if(m_pnetnodesocket != NULL)
      {
         return m_pnetnodesocket->response().file();
      }
      else
      {
         return *m_spmemoryfileFallback;
      }
   }

   void script_interface::on_initialize()
   {
   }
    
   void script_interface::initialize(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager)
   {
      
      m_pinstanceMain      = pinterfaceMain;
      m_pinstanceParent    = pinterfaceParent;
      m_pnetnodesocket     = pdssocket;
      m_pmanager           = pmanager;
      
      on_initialize();

   }

} // namespace dynamic_source



