#include "framework.h"


namespace user
{


   namespace uinteraction
   {


      uinteraction::uinteraction(base_application * papp) :
         element(papp),
         base_departament(papp)
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

         ::core::library library(get_app(), NULL);

         string strLibrary(strId);

         strLibrary.replace("-", "_");

         strLibrary.replace("/", "_");

#if defined(LINUX) || defined(MACOS)

         strLibrary = "lib" + strLibrary;

#elif defined(METROWIN)


         //      strLibrary = "m_" + strLibrary;

#endif

         if(!library.open(strLibrary, false))
            return NULL;

         stringa stra;

         library.get_app_list(stra);

         if(stra.get_size() != 1) // a uinteraction OSLibrary should have one uinteraction
            return NULL;

         string strAppId(stra[0]);

         if(strAppId.is_empty()) // trivial validity check
            return NULL;

         sp(::user::uinteraction::interaction) pinteraction = library.get_new_uinteraction();

         if(pinteraction == NULL)
            return NULL;

         return pinteraction;

      }


      sp(::user::uinteraction::interaction) uinteraction::get_uinteraction(const char * pszUinteraction)
      {

         if(System.get_twf() == NULL)
         {

            System.defer_initialize_twf();

         }

         sp(::user::uinteraction::interaction) pinteraction = Session.m_mapUinteraction[pszUinteraction];

         if(Session.m_mapUinteraction[pszUinteraction] == NULL)
         {

            Session.m_mapUinteraction[pszUinteraction] = Session.uinteraction().get_new_uinteraction(pszUinteraction);

            pinteraction = Session.m_mapUinteraction[pszUinteraction];

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




