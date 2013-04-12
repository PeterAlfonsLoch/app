#include "framework.h"


namespace uinteraction
{


   uinteraction::uinteraction()
   {

   }


   uinteraction::~uinteraction()
   {

   }


   sp(::uinteraction::interaction) uinteraction::get_new_uinteraction(const char * pszUinteractionLibrary)
   {

      string strId(pszUinteractionLibrary);

      string strBuildNumber = System.command()->m_varTopicQuery["build_number"];

      if(strBuildNumber.is_empty())
      {

         strBuildNumber = "latest";

      }

#ifndef METROWIN
      if(!System.directrix()->m_varTopicQuery.has_property("install")
      && !System.directrix()->m_varTopicQuery.has_property("uninstall")
      && !System.install().is(::null(), strBuildNumber, "uinteraction", strId, Application.m_strLocale, Application.m_strSchema))
      {

         throw not_installed(get_app(), ::null(), strBuildNumber, "uinteraction", strId, Application.m_strLocale, Application.m_strSchema);

      }

#endif

      ::ca::library library(::null());

      string strLibrary(strId);

      strLibrary.replace("-", "_");

      strLibrary.replace("/", "_");

#ifdef LINUX

      strLibrary = "lib" + strLibrary;

#elif defined(METROWIN)


//      strLibrary = "m_" + strLibrary;

#endif

      if(!library.open(get_app(), strLibrary, false))
         return ::null();

      stringa stra;

      library.get_app_list(stra);

      if(stra.get_size() != 1) // a uinteraction OSLibrary should have one uinteraction
         return ::null();

      string strAppId(stra[0]);

      if(strAppId.is_empty()) // trivial validity check
         return ::null();

      sp(::uinteraction::interaction) pinteraction = library.get_new_uinteraction();
      if(pinteraction == ::null())
         return ::null();

      return pinteraction;

   }

   sp(::uinteraction::interaction) uinteraction::get_uinteraction(const char * pszUinteraction)
   {

      if(System.get_twf() == ::null())
      {

         System.create_twf();

      }

      sp(::uinteraction::interaction) pinteraction = Bergedge.m_mapUinteraction[pszUinteraction];

      if(Bergedge.m_mapUinteraction[pszUinteraction] == ::null())
      {

         Bergedge.m_mapUinteraction[pszUinteraction] = Bergedge.uinteraction().get_new_uinteraction(pszUinteraction);

         pinteraction = Bergedge.m_mapUinteraction[pszUinteraction];

      }

      return pinteraction;


   }


   sp(::uinteraction::frame::frame) uinteraction::get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName)
   {

      sp(::uinteraction::interaction) pinteraction = get_uinteraction(pszLibrary);

      if(pinteraction == ::null())
         return ::null();


      return pinteraction->get_frame_schema(pszFrameSchemaName);

   }


} // namespace uinteraction




