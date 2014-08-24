#include "framework.h"


namespace user
{


   namespace wndfrm
   {


      wndfrm::wndfrm(sp(::aura::application) papp) :
         element(papp),
         ::aura::departament(papp)
      {

      }


      wndfrm::~wndfrm()
      {

      }


      sp(::user::wndfrm::interaction) wndfrm::get_new_uinteraction(const char * pszUinteractionLibrary)
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
            && !System.install().is(NULL, strBuildNumber, "wndfrm", strId, Application.m_strLocale, Application.m_strSchema))
         {

            throw not_installed(get_app(), NULL, strBuildNumber, "wndfrm", strId, Application.m_strLocale, Application.m_strSchema);

         }

#endif

#endif

         ::aura::library library(get_app(), 0, NULL);

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

         if(stra.get_size() != 1) // a wndfrm OSLibrary should have one wndfrm
            return NULL;

         string strAppId(stra[0]);

         if(strAppId.is_empty()) // trivial validity check
            return NULL;

         sp(::user::wndfrm::interaction) pinteraction = library.create_object(get_app(), "wndfrm");

         if(pinteraction == NULL)
            return NULL;

         return pinteraction;

      }


      sp(::user::wndfrm::interaction) wndfrm::get_uinteraction(const char * pszUinteraction)
      {

         if(System.get_twf() == NULL)
         {

            if(!System.defer_initialize_twf())
               return NULL;

         }

         sp(::user::wndfrm::interaction) pinteraction = Platform.m_mapUinteraction[pszUinteraction];

         if(Platform.m_mapUinteraction[pszUinteraction] == NULL)
         {

            Platform.m_mapUinteraction[pszUinteraction] = Platform.wndfrm().get_new_uinteraction(pszUinteraction);

            pinteraction = Platform.m_mapUinteraction[pszUinteraction];

         }

         return pinteraction;


      }


      sp(::user::wndfrm::frame::frame) wndfrm::get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName)
      {

         sp(::user::wndfrm::interaction) pinteraction = get_uinteraction(pszLibrary);

         if(pinteraction == NULL)
            return NULL;


         return pinteraction->get_frame_schema(pszFrameSchemaName);

      }


   } // namespace wndfrm




} // namespace user




