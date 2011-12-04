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

      return TRUE;
   }


   bool cube::process_initialize()
   {

      return true;
   }


   bool cube::initialize()
   {

      return true;
   }



   bool cube::initialize1()
   {




      return true;

   }



   bool cube::initialize3()
   {

      
      return true;


   }

   bool cube::initialize_instance()
   {


      return true;


   }


   bool cube::bergedge_start()
   {
      return true;
   }


   int cube::exit_instance()
   {


      return 0;


   }



   bergedge::bergedge * cube::query_bergedge(index iEdge)
   {
      bergedge::bergedge * pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         return NULL;
      }
      return pbergedge;
   }


   bergedge::bergedge * cube::get_bergedge(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      bergedge::bergedge * pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         pbergedge = dynamic_cast < ::bergedge::bergedge * > (create_application("bergedge", true, pbiasCreation));
         if(pbergedge == NULL)
            return NULL;
         pbergedge->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, pbergedge);
      }
      return pbergedge;
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
      cube::application::finalize();


      return true;
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
      bergedge::bergedge * pbergedge;
      while(m_pbergedgemap->Lookup(iNewEdge, pbergedge))
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

   unsigned long cube::guess_code_page(const char * pszText)
   {
      if(!m_bLibCharGuess)
      {
         LibCharGuess::Init();
         m_bLibCharGuess = true;
      }
      return LibCharGuess::GuessCodePage(pszText);
   }


   ::ca::application * cube::get_new_app(::ca::application * pappNewApplicationParent, const char * pszAppId)
   {

      ca2::library library;

      string strLibrary = m_mapAppLibrary[pszAppId];

      ::ca::application * papp = NULL;
      if(!library.open(pappNewApplicationParent, strLibrary, false))
         return NULL;

      papp = library.get_new_app(pszAppId);
      if(papp == NULL)
         return NULL;

      return papp;

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



