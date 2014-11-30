#include "framework.h"
#include "dynamic_source.h"


namespace dynamic_source
{


   script_interface::script_interface()
   {

      if(get_app() != NULL)
      {
         m_spmemoryfileFallback = canew(::file::memory_buffer(get_app()));
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


   property & script_interface::get(const char * pszKey)
   {
      return oprop(pszKey);
   }


   bool script_interface::main_initialize()
   {

      return true;

   }

   bool script_interface::main_finalize()
   {

      m_pnetnodesocket     = NULL;
      m_pmanager           = NULL;

      m_pscript            = NULL;
      m_pinstanceMain      = NULL;
      m_pinstanceParent    = NULL;

      return true;

   }

   ::file::stream_buffer & script_interface::output_file()
   {
      if(m_pinstanceMain == this)
      {
         return *((::file::stream_buffer *) NULL);
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
         m_ostreamFallback.m_spbuffer = m_spmemoryfileFallback;
         return *m_ostreamFallback.m_spbuffer;
      }
   }

   ::file::output_stream & script_interface::ostream()
   {
      if(m_pinstanceMain == this)
      {
         return *((::file::output_stream *) NULL);
      }
      else if(m_pinstanceMain != NULL)
      {
         return m_pinstanceMain->ostream();
      }
      else if(m_pnetnodesocket != NULL)
      {
         return m_pnetnodesocket->response().ostream();
      }
      else
      {
         m_ostreamFallback.m_spbuffer = m_spmemoryfileFallback;
         return m_ostreamFallback;
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

   void script_interface::set_session_value(id, var)
   {

   }


   var script_interface::get_session_value(id)
   {

      return var(var::type_new);

   }

   string script_interface::session_id(const char *)
   {

      return "";

   }
} // namespace dynamic_source



