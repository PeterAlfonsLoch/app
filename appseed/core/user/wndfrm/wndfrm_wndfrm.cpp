//#include "framework.h"


namespace user
{


   namespace wndfrm
   {


      wndfrm::wndfrm(::aura::application * papp) :
         object(papp),
         ::aura::departament(papp)
      {

      }


      wndfrm::~wndfrm()
      {

      }


      sp(::user::wndfrm::interaction) wndfrm::get_new_wndfrm(const char * pszUinteractionLibrary)
      {

         string strId(pszUinteractionLibrary);

         string strBuildNumber = System.command()->m_varTopicQuery["build_number"];

         if(strBuildNumber.is_empty())
         {

            strBuildNumber = "installed";

         }

#ifdef CUBE

         // should implemente

#else


#endif

         ::aura::library * plibrary = new ::aura::library(get_app(),0,NULL);

         ::aura::library & library = *plibrary;

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
         {

            delete plibrary;



            return NULL;

         }

         pinteraction->m_plibrary = plibrary;

         return pinteraction;

      }


      sp(::user::wndfrm::interaction) wndfrm::get_wndfrm(const char * pszUinteraction)
      {

         if(System.get_twf() == NULL)
         {

            if(!System.defer_initialize_twf())
               return NULL;

         }

         sp(::user::wndfrm::interaction) pinteraction = Session.m_mapUinteraction[pszUinteraction];

         if(Session.m_mapUinteraction[pszUinteraction] == NULL)
         {

            Session.m_mapUinteraction[pszUinteraction] = Session.wndfrm().get_new_wndfrm(pszUinteraction);

            pinteraction = Session.m_mapUinteraction[pszUinteraction];

         }

         return pinteraction;


      }


      sp(::user::wndfrm::frame::frame) wndfrm::get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName)
      {

         string strLibrary(pszLibrary);

         if(strLibrary.is_empty())
         {

            string strConfig = Application.file().as_string("C:\\ca2\\config\\system\\wndfrm.txt");

            strLibrary = string("wndfrm_") + strConfig;

         }

         sp(::user::wndfrm::interaction) pinteraction = get_wndfrm(strLibrary);

         if(pinteraction == NULL)
         {

            wndfrm_core:

            strLibrary = "wndfrm_core";

            pinteraction = get_wndfrm(strLibrary);

            if(pinteraction == NULL)
            {

               Application.simple_message_box("no wndfrm plugin", "no wndfrm plugin", MB_OK);

               return NULL;

            }

         }


         sp(::user::wndfrm::frame::frame) pframe = pinteraction->get_frame_schema(pszFrameSchemaName);

         if(pframe.is_null() && strLibrary != "wndfrm_core")
         {

            goto wndfrm_core;

         }

         if(pframe.is_null())
         {

            Application.simple_message_box("no wndfrm plugin able to produce window frame", "no wndfrm plugin able to produce window frame", MB_OK);

            return NULL;

         }

         pframe->m_pinteraction = pinteraction;

         return pframe;

      }


   } // namespace wndfrm




} // namespace user




