#include "framework.h"



namespace aura
{


   session::session(sp(::aura::application) papp) :
      element(papp),
      ::thread(papp)
   {

      m_paurasession    = this;

      m_pcoreplatform   = NULL;

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

      throw interface_only_exception(this);

      return NULL;

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

      string strLocaleSystem;

      string strSchemaSystem;

      string strPath = System.dir_appdata("langstyle_settings.xml");

      if(file_exists(strPath))
      {

         string strSystem = file_as_string(strPath);

         ::xml::document docSystem(get_app());

         if(docSystem.load(strSystem))
         {

            if(docSystem.get_child("lang") != NULL)
            {

               strLocaleSystem = docSystem.get_child("lang")->get_value();

            }

            if(docSystem.get_child("style") != NULL)
            {

               strSchemaSystem = docSystem.get_child("style")->get_value();

            }

         }

      }

      string strLocale;

      string strSchema;

#ifdef METROWIN

      stringa stra;

      try
      {

         stra.explode("-",::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride);

      }
      catch(long)
      {


      }

      strLocale = stra[0];

      strSchema = stra[0];

#elif defined(WINDOWS)

      LANGID langid = ::GetUserDefaultLangID();

#define SPR_DEUTSCH LANG_GERMAN

      if(langid == LANG_SWEDISH)
      {
         strLocale = "se";
         strSchema = "se";
      }
      else if(langid == MAKELANGID(LANG_PORTUGUESE,SUBLANG_PORTUGUESE_BRAZILIAN))
      {
         strLocale = "pt-br";
         strSchema = "pt-br";
      }
      else if(PRIMARYLANGID(langid) == SPR_DEUTSCH)
      {
         strLocale = "de";
         strSchema = "de";
      }
      else if(PRIMARYLANGID(langid) == LANG_ENGLISH)
      {
         strLocale = "en";
         strSchema = "en";
      }
      else if(PRIMARYLANGID(langid) == LANG_JAPANESE)
      {
         strLocale = "jp";
         strSchema = "jp";
      }
      else if(PRIMARYLANGID(langid) == LANG_POLISH)
      {
         strLocale = "pl";
         strSchema = "pl";
      }

#endif

      if(strLocale.is_empty())
         strLocale = "se";

      if(strSchema.is_empty())
         strSchema = "se";

      if(strLocaleSystem.has_char())
         strLocale = strLocaleSystem;

      if(strSchemaSystem.has_char())
         strSchema = strSchemaSystem;

      if(Sys(this).directrix()->m_varTopicQuery["locale"].get_count() > 0)
         strLocale = Sys(this).directrix()->m_varTopicQuery["locale"].stra()[0];

      if(Sys(this).directrix()->m_varTopicQuery["schema"].get_count() > 0)
         strSchema = Sys(this).directrix()->m_varTopicQuery["schema"].stra()[0];

      if(App(this).directrix()->m_varTopicQuery["locale"].get_count() > 0)
         strLocale = App(this).directrix()->m_varTopicQuery["locale"].stra()[0];

      if(App(this).directrix()->m_varTopicQuery["schema"].get_count() > 0)
         strSchema = App(this).directrix()->m_varTopicQuery["schema"].stra()[0];


      set_locale(strLocale,::action::source::database());
      set_schema(strSchema,::action::source::database());




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


   void session::set_locale(const string & lpcsz,::action::context actioncontext)
   {
      string strLocale(lpcsz);
      strLocale.trim();
      m_strLocale = strLocale;
      on_set_locale(m_strLocale,actioncontext);
   }

   void session::set_schema(const string & lpcsz,::action::context actioncontext)
   {
      string strSchema(lpcsz);
      strSchema.trim();
      m_strSchema = strSchema;
      on_set_schema(m_strSchema,actioncontext);
   }

   void session::on_set_locale(const string & lpcsz,::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
   }

   void session::on_set_schema(const string & lpcsz,::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
   }


   string session::get_locale()
   {
      return m_strLocale;
   }

   string session::get_schema()
   {
      return m_strSchema;
   }


   string session::get_locale_schema_dir()
   {

      return dir_simple_path(get_locale(),get_schema());

   }


   string session::get_locale_schema_dir(const string & strLocale)
   {

      if(strLocale.is_empty())
      {

         return dir_simple_path(get_locale(),get_schema());

      }
      else
      {

         return dir_simple_path(strLocale,get_schema());

      }

   }


   string session::get_locale_schema_dir(const string & strLocale,const string & strSchema)
   {

      if(strLocale.is_empty())
      {

         if(strSchema.is_empty())
         {

            return dir_simple_path(get_locale(),get_schema());

         }
         else
         {

            return dir_simple_path(get_locale(),strSchema);

         }

      }
      else
      {

         if(strSchema.is_empty())
         {

            return dir_simple_path(strLocale,get_schema());

         }
         else
         {

            return dir_simple_path(strLocale,strSchema);

         }

      }

   }


   void session::fill_locale_schema(::str::international::locale_schema & localeschema,const char * pszLocale,const char * pszSchema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      string strLocale(pszLocale);
      string strSchema(pszSchema);


      localeschema.m_idLocale = pszLocale;
      localeschema.m_idSchema = pszSchema;


      localeschema.add_locale_variant(strLocale,strSchema);
      localeschema.add_locale_variant(get_locale(),strSchema);
      localeschema.add_locale_variant(__id(std),strSchema);
      localeschema.add_locale_variant(__id(en),strSchema);


      localeschema.finalize();


   }


   void session::fill_locale_schema(::str::international::locale_schema & localeschema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      //localeschema.m_bAddAlternateStyle = true;


      stringa straLocale;
      stringa straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      stringa stra;

      stra = Application.directrix()->m_varTopicQuery["locale"].stra();

      stra.remove_ci("_std");

      straLocale.add_unique(Application.directrix()->m_varTopicQuery["locale"].stra());

      stra = Application.directrix()->m_varTopicQuery["schema"].stra();

      stra.remove_ci("_std");

      straSchema.add_unique(Application.directrix()->m_varTopicQuery["schema"].stra());


      localeschema.m_idLocale = straLocale[0];
      localeschema.m_idSchema = straSchema[0];

      for(index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for(index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale],straSchema[iSchema]);

         }

      }

      for(index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(),straSchema[iSchema]);

      }

      for(index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(std),straSchema[iSchema]);

      }


      for(index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(en),straSchema[iSchema]);

      }

      localeschema.finalize();


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
































