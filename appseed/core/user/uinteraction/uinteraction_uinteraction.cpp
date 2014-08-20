#include "framework.h"


namespace user
{


   namespace uinteraction
   {


      uinteraction::uinteraction(sp(::axis::application) papp) :
         element(papp),
         ::axis::departament(papp)
      {

      }


      uinteraction::~uinteraction()
      {

      }


      sp(::user::uinteraction::interaction) uinteraction::get_new_uinteraction(const char * pszUinteractionLibrary)
      {

         string strId(pszUinteractionLibrary);

         string strBuildNumber = System.command()->m_varTopicQuery["build_number"];

         if(strBuildNumber.is_empty())
         {

            strBuildNumber = "latest";

         }

#ifdef CUBE

         // should implemente

#else

#ifndef METROWIN
         if(!System.directrix()->m_varTopicQuery.has_property("install")
            && !System.directrix()->m_varTopicQuery.has_property("uninstall")
            && !System.install().is(NULL, strBuildNumber, "uinteraction", strId, Application.m_strLocale, Application.m_strSchema))
         {

            throw not_installed(get_app(), NULL, strBuildNumber, "uinteraction", strId, Application.m_strLocale, Application.m_strSchema);

         }

#endif

#endif

         ::axis::library library(get_app(), 0, NULL);

         string strLibrary(strId);

         strLibrary.replace("-", "_");

         strLibrary.replace("/", "_");

#if defined(LINUX) || defined(APPLEOS)

         strLibrary = "lib" + strLibrary;

#elif defined(METROWIN)


         //      strLibrary = "m_" + strLibrary;

#endif

         if(!library.open(strLibrary, false))
            return NULL;

         if(!library.open_ca2_library())
            return NULL;

         stringa stra;

         library.get_app_list(stra);

         if(stra.get_size() != 1) // a uinteraction OSLibrary should have one uinteraction
            return NULL;

         string strAppId(stra[0]);

         if(strAppId.is_empty()) // trivial validity check
            return NULL;

         sp(::user::uinteraction::interaction) pinteraction = library.create_object(get_app(), "uinteraction");

         if(pinteraction == NULL)
            return NULL;

         return pinteraction;

      }


      sp(::user::uinteraction::interaction) uinteraction::get_uinteraction(const char * pszUinteraction)
      {

         if(System.get_twf() == NULL)
         {

            if(!System.defer_initialize_twf())
               return NULL;

         }

         sp(::user::uinteraction::interaction) pinteraction = platform().m_mapUinteraction[pszUinteraction];

         if(platform().m_mapUinteraction[pszUinteraction] == NULL)
         {

            platform().m_mapUinteraction[pszUinteraction] = platform().uinteraction().get_new_uinteraction(pszUinteraction);

            pinteraction = platform().m_mapUinteraction[pszUinteraction];

         }

         return pinteraction;


      }


      sp(::user::uinteraction::frame::frame) uinteraction::get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName)
      {

         sp(::user::uinteraction::interaction) pinteraction = get_uinteraction(pszLibrary);

         if(pinteraction == NULL)
            return NULL;


         return pinteraction->get_frame_schema(pszFrameSchemaName);

      }


   } // namespace uinteraction




} // namespace user




