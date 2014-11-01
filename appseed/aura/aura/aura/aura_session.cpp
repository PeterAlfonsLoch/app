#include "framework.h"



namespace aura
{


   session::session(sp(::aura::application) papp) :
      element(papp),
      ::thread(papp)
   {

      m_paurasession    = this;

      m_bMatterFromHttpCache = m_paurasystem->m_bMatterFromHttpCache;

#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance = m_pauraapp->m_hinstance;

      }

#endif

      m_psavings                 = canew(class ::aura::savings(this));

      m_bZipIsDir                = true;

      m_paurasystem->m_basesessionptra.add_unique(this);

   }


   void session::construct(sp(::aura::application) papp, int iPhase)
   {

   }


   session::~session_parent
   {

      m_paurasystem->m_basesessionptra.remove(this);

      POSITION pos = m_mapApplication.get_start_position();

      string strId;

      sp(::aura::application) pbaseapp;

      while(pos != NULL)
      {

         strId.Empty();

         pbaseapp = NULL;

         m_mapApplication.get_next_assoc(pos,strId,pbaseapp);

         sp(::aura::application) papp = (pbaseapp);

         papp->post_thread_message(WM_QUIT);

      }

   }


   bool session::is_session()
   {

      return true;

   }


   sp(::aura::application) session::start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext)
   {

      return m_pplatform->start_application(pszType,pszAppId,pcreatecontext);

   }






   COLORREF session::get_default_color(uint64_t ui)
   {

      switch(ui)
      {
      case COLOR_3DFACE:
         return ARGB(127,192,192,184);
      case COLOR_WINDOW:
         return ARGB(127,255,255,255);
      case COLOR_3DLIGHT:
         return ARGB(127,218,218,210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127,238,238,230);
      case COLOR_3DSHADOW:
         return ARGB(127,138,138,130);
      case COLOR_3DDKSHADOW:
         return ARGB(127,84,84,77);
      default:
         break;
      }

      return ARGB(127,0,0,0);

   }






   bool  session::get_window_minimum_size(LPSIZE lpsize)
   {

      lpsize->cx = 184 + 177;

      lpsize->cy = 184 + 177;

      return true;

   }




   bool session::process_initialize()
   {

      if(!::aura::application::process_initialize())
         return false;

      return true;

   }


   bool session::initialize1()
   {

      if(!::aura::application::initialize1())
         return false;





      return true;

   }


   bool session::initialize2()
   {

      if(!::aura::application::initialize2())
         return false;

      return true;

   }



   bool session::initialize_instance()
   {




      if(!::aura::application::initialize_instance())
         return false;


      return true;

   }


   bool session::initialize()
   {

      if(!::aura::application::initialize())
         return false;


      return true;

   }


   bool session::finalize()
   {

      bool bOk = true;


      try
      {

         bOk = ::aura::application::finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      return bOk;

   }


   int32_t session::exit_instance()
   {


      ::aura::application::exit_instance();

      return 0;

   }


   application_ptra & session::appptra()
   {

      return m_appptra;

   }








   void session::frame_pre_translate_message(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   ::user::interaction * session::get_active_guie()
   {

      return NULL;

   }


   ::user::interaction * session::get_focus_guie()
   {


      return NULL;

   }




   bool session::is_licensed(const char * pszId,bool bInteractive)
   {

      throw not_implemented(get_app());

   }




} // namespace aura
































