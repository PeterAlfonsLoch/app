#include "StdAfx.h"

#undef new
#include <GdiPlus.h>
#define new DEBUG_NEW


namespace cube
{

   cube::cube()
   {


      m_prunstartinstaller       = NULL;

      

   }

   cube::~cube()
   {
      m_puiMain      = NULL;
      m_puiActive    = NULL;


   }

   BOOL cube::InitApplication()
   {

      if(!::cube8::application::InitApplication())
         return FALSE;

      return TRUE;

   }


   bool cube::process_initialize()
   {

      if(!::cube8::application::process_initialize())
         return false;

      return true;

   }


   bool cube::initialize()
   {

      if(!::cube8::application::initialize())
         return false;

      return true;

   }



   bool cube::initialize1()
   {

      if(!::cube8::application::initialize1())
         return false;

      return true;

   }



   bool cube::initialize3()
   {

      if(!::cube8::application::initialize3())
         return false;
      
      return true;

   }

   bool cube::initialize_instance()
   {

      if(!::cube8::application::initialize_instance())
         return false;

      return true;

   }


   bool cube::bergedge_start()
   {

      if(!::cube8::application::bergedge_start())
         return false;

      return true;
   }


   int cube::exit_instance()
   {

      int iRet = -1;

      try
      {
         iRet = ::cube8::application::exit_instance();
      }
      catch(...)
      {
      }
         


      return iRet;


   }



   bergedge::bergedge * cube::query_bergedge(index iEdge)
   {
      plane::session * psession = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         return NULL;
      }
      return dynamic_cast < ::bergedge::bergedge * > (psession->m_pbergedge);
   }


   bergedge::bergedge * cube::get_bergedge(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      plane::session * psession = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         psession = dynamic_cast < ::plane::session * > (create_application("session", true, pbiasCreation));
         if(psession == NULL)
            return NULL;
         psession->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, psession);
      }
      return dynamic_cast < ::bergedge::bergedge * > (psession->m_pbergedge);
   }


   platform::document * cube::get_platform(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      bergedge::bergedge * pbergedge = get_bergedge(iEdge, pbiasCreation);
      return pbergedge->get_platform();
   }

   nature::document * cube::get_nature(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      bergedge::bergedge * pbergedge = get_bergedge(iEdge, pbiasCreation);
      return pbergedge->get_nature();
   }

   ::ca::application * cube::application_get(index iEdge, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      bergedge::bergedge * pbergedge = get_bergedge(iEdge, pbiasCreate);
      return pbergedge->application_get(pszId, bCreate, bSynch, pbiasCreate);
   }


   bool cube::set_history(::ca::history * phistory)
   {
      return true;
   }


   ::ca2::filehandler::handler & cube::filehandler()
   {
      return *m_spfilehandler;
   }

   void cube::register_bergedge_application(::ca::application * papp)
   {
      
      
      System.register_bergedge_application(papp);


   }

   void cube::unregister_bergedge_application(::ca::application * papp)
   {

      System.unregister_bergedge_application(papp);


   }






   bool cube::finalize()
   {

      bool bOk = false;

      try
      {
         bOk = cube::application::finalize();
      }
      catch(...)
      {
      }


      return bOk;
   }


   void cube::on_request(::ca::create_context * pcreatecontext)
   {
      ::bergedge::bergedge * pbergedge = get_bergedge(pcreatecontext->m_spCommandLine->m_iEdge, pcreatecontext->m_spCommandLine->m_pbiasCreate);
      pbergedge->request(pcreatecontext);
   }

   void cube::open_by_file_extension(index iEdge, const char * pszFileName)
   {
      get_bergedge(iEdge)->open_by_file_extension(pszFileName);
   }


   bool cube::base_support()
   {
      return true;
   }

   index cube::get_new_bergedge(::ca::application_bias * pbiasCreation)
   {
      int iNewEdge = m_iNewEdge;
      plane::session * psession;
      while(m_pbergedgemap->Lookup(iNewEdge, psession))
      {
         iNewEdge++;
      }
      if(get_bergedge(iNewEdge, pbiasCreation) == NULL)
         return -1;
      m_iNewEdge = iNewEdge + 1;
      return iNewEdge;
   }


   bool cube::is_system()
   {
      return true;
   }

   bool cube::set_main_init_data(::ca::main_init_data * pdata)
   {

      if(pdata == NULL)
      {
         if(!::cube8::application::set_main_init_data(pdata))
            return false;
         return true;
      }
      
      gen::property_set set(this);

      var varFile;
      string strApp;

      set._008ParseCommandFork(pdata->m_vssCommandLine, varFile, strApp);

      if((varFile.is_empty() && ((!set.has_property("app") && !set.has_property("show_platform"))
         || set["app"] == "bergedge")) &&
         !(set.has_property("install") || set.has_property("uninstall")))
      {
         if(!set.has_property("show_platform") || set["show_platform"] == 1)
         {
            command().add_line(" : show_platform=1");
         }
      }
      else
      {
         string strCommandLine = pdata->m_vssCommandLine;
         strCommandLine.trim();
         if(strCommandLine[0] == '\"')
         {
            int iFind = strCommandLine.find("\"", 1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         else
         {
            int iFind = strCommandLine.find(" ", 1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         command().add_line(strCommandLine);
      }

      if(!::cube8::application::set_main_init_data(pdata))
         return false;
      
      return true;

   }


} // namespace cube



