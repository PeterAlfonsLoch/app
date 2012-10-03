#include "framework.h"


namespace uinteraction
{

   application::application()
   {
   }

   application::~application()
   {
   }


   ::uinteraction::interaction * application::get_new_uinteraction(const char * pszUinteractionLibrary)
   {

      string strId(pszUinteractionLibrary);

      string strBuildNumber = System.command().m_varTopicQuery["build_number"];

      if(strBuildNumber.is_empty())
      {
         
         strBuildNumber = "latest";

      }

      if(!System.directrix().m_varTopicQuery.has_property("install")
      && !System.directrix().m_varTopicQuery.has_property("uninstall")
      && !System.install().is(NULL, strBuildNumber, "uinteraction", strId, m_strLocale, m_strSchema))
      {

         throw not_installed(NULL, strBuildNumber, "uinteraction", strId, m_strLocale, m_strSchema);

      }

      ca2::library library(NULL);

      string strLibrary(strId);

      strLibrary.replace("-", "_");

      strLibrary.replace("/", "_");
      
      if(!library.open(get_app(), strLibrary, false))
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

      if(System.get_twf() == NULL)
      {

         System.create_twf();

      }
      
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