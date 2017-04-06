//#include "framework.h"


namespace user
{


   namespace wndfrm
   {


      wndfrm::wndfrm(::aura::application * papp) :
         object(papp),
         ::aura::department(papp)
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

         ::aura::library * plibrary = canew(::aura::library(get_app(),0,NULL));

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

         sp(::user::wndfrm::interaction) pinteraction = library.create_object(get_app(), "wndfrm", NULL);

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

         stringa straLibrary;

         {

            string strLibrary(pszLibrary);

            if (strLibrary.has_char())
            {

               straLibrary.add(strLibrary);

            }

         }

         {

            string strLibrary = Application.preferred_userschema();

            if (strLibrary.has_char())
            {

               straLibrary.add(strLibrary);

            }

         }

         {

            string strConfig = Application.directrix()->m_varTopicQuery["wndfrm"];

            if (strConfig.has_char())
            {

               string strLibrary = string("wndfrm_") + strConfig;

               straLibrary.add(strConfig);

            }

         }
            
            
         {

            string strConfig = Application.file().as_string(::dir::system() / "config\\system\\wndfrm.txt");

            if (strConfig.has_char())
            {

               string strLibrary = string("wndfrm_") + strConfig;

               straLibrary.add(strLibrary);

            }

         }

         straLibrary.add("wndfrm_metro");
         straLibrary.add("wndfrm_rootkiller");
         straLibrary.add("wndfrm_hyper");
         straLibrary.add("wndfrm_core");

         sp(::user::wndfrm::interaction) pinteraction;

         for(string strLibrary : straLibrary)
         {

            pinteraction = get_wndfrm(strLibrary);

            if (pinteraction.is_set())
            {

               break;

            }

         }

         if (pinteraction.is_null())
         {

            throw exit_exception(get_app(), "wndfrm_core plugin or any other wndfrm_* plugin is installed");

         }

         sp(::user::wndfrm::frame::frame) pframe = pinteraction->get_frame_schema(pszFrameSchemaName);

         if(pframe.is_null())
         {

            Application.simple_message_box(NULL, "no wndfrm plugin able to produce window frame", MB_OK);

            return NULL;

         }

         pframe->m_pinteraction = pinteraction;

         return pframe;

      }


   } // namespace wndfrm




} // namespace user







namespace core
{


   bool application::initialize1_wndfrm()
   {


      thisstart;

      m_pwndfrm = canew(::user::wndfrm::wndfrm(this));

      if (m_pwndfrm == NULL)
      {

         thiserr << "end failure (1)";

         return false;

      }

      wndfrm().construct(this);

      if (!wndfrm().initialize())
      {

         thiserr << "end failure (2)";

         return false;

      }

      thisend;

      return true;

   }

   ::user::wndfrm::wndfrm          &application::wndfrm()
   {

      return *m_pwndfrm.cast < ::user::wndfrm::wndfrm>();

   }


} // namespace core