#include "framework.h"


namespace uinteraction
{

   application::application()
   {
   }

   application::~application()
   {
   }


   ::uinteraction::interaction * application::get_new_uinteraction(const char * pszUinteraction)
   {

      string strLibrary = string(pszUinteraction) + "_uinteraction";

      if(!System.directrix().m_varTopicQuery.has_property("install")
      && !System.directrix().m_varTopicQuery.has_property("uninstall")
      && !System.install().is("uinteraction", strLibrary))
      {

         if(::IsDebuggerPresent())
         {

            MessageBox(NULL, "Debug Only Message\n\nPlease install \"" + strLibrary + "\"", "Debug Only - Please Install - ca2", MB_OK);

            return NULL;

         }

         hotplugin::host::starter_start(": app=session session_start=" + strLibrary + " app_type=uinteraction install", NULL);

         return NULL;

      }

      ca2::library library;

      
      if(!library.open(get_app(), "app_" + strLibrary, false))
         return NULL;

      stringa stra;

      library.get_app_list(stra);

      if(stra.get_size() != 1) // a uinteraction OSLibrary should have one application
         return NULL;

      string strAppId(stra[0]);

      if(strAppId.is_empty()) // trivial validity check
         return NULL;



      ::uinteraction::interaction * pinteraction = library.get_new_uinteraction();
      if(pinteraction == NULL)
         return NULL;

      return pinteraction;

   }

   ::uinteraction::interaction * application::get_uinteraction(const char * pszUinteraction)
   {
      
      ::uinteraction::interaction * pinteraction = Bergedge.m_mapUinteraction[pszUinteraction];

      if(Bergedge.m_mapUinteraction[pszUinteraction] == NULL)
      {

         Bergedge.m_mapUinteraction[pszUinteraction] = Bergedge.get_new_uinteraction(pszUinteraction);

         pinteraction = Bergedge.m_mapUinteraction[pszUinteraction];

      }

      return pinteraction;


   }


   ::uinteraction::frame::frame * application::get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName)
   {

      ::uinteraction::interaction * pinteraction = get_uinteraction(pszLibrary);

      if(pinteraction == NULL)
         return NULL;


      return pinteraction->get_frame_schema(pszFrameSchemaName);

   }

} // namespace uinteraction