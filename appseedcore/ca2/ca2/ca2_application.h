#pragma once

#include "ca2_html.h"
#include "ca2_process.h"

namespace ca
{

   class CLASS_DECL_ca application_ptra :
      virtual public comparable_array < ::ca::application *, ::ca::application * >
   {
   };

} // namespace ca


namespace fontopus
{

   class user;

} // namespace fontopus


namespace ca2
{

   class CLASS_DECL_ca application_request
   {
   public:


      ::user::interaction *      m_puiParent;
      index                      m_iEdge;
      string                     m_strApp;
      var                        m_varFile;
      var                        m_varQuery;
      manual_reset_event         m_eventReady;
      ::ca::application_bias *   m_pbiasCreate;


      application_request();

   };

   class CLASS_DECL_ca application :
      virtual public ::xml::application
   {
   public:
      ::collection::map < string, string, string_to_string_map *, string_to_string_map * > m_stringtablemap;
      ::collection::map < string, string, string_to_string_map *, string_to_string_map * > m_stringtablemapStd;
      comparable_array < language_string *, language_string * > m_langstrptra;
      string                              m_strLocale;
      string                              m_strStyle;
      manual_reset_event *                m_peventReady;

      
      string                              m_strLicense;
      string                              m_strBaseSupportId;


      


      application();
      virtual ~application();


      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      virtual int run();

      virtual string get_locale();
      virtual string get_style();
      virtual string get_locale_style_dir();

      virtual void EnableShellOpen();

      virtual bool open_link(const char * pszLink, const char * pszTarget = NULL);




      virtual void set_locale(const char * lpcsz, bool bUser);
      virtual void set_style(const char * lpcsz, bool bUser);
      virtual void on_set_locale(const char * lpcsz, bool bUser);
      virtual void on_set_style(const char * lpcsz, bool bUser);

      
      virtual ::fontopus::user * create_current_user();


      virtual bool initialize1();
      virtual bool initialize();
      virtual bool finalize();

      virtual void _001CloseApplication();




      //virtual string get_current_user_login();

      virtual string load_string(id id);
      bool load_cached_string(string & str, id id, bool bLoadStringTable);
      bool load_cached_string_by_id(string & str, id id, const char * pszFallbackValue, bool bLoadStringTable);
      void load_string_table(const char * pszId);

      virtual bool get_auth(const char * pszForm, string & strUsername, string & strPassword);

      virtual bool base_support();

      virtual string message_box(const char * pszMatter, gen::property_set & propertyset);


      virtual void load_string_table();

      virtual ::user::interaction * uie_from_point(point pt);

      virtual bool bergedge_start();

      void process(machine_event_data * pdata);

      virtual void pre_translate_message(gen::signal_object * pobj);

      ::mutex * get_local_mutex();
      ::mutex * get_global_mutex();

      virtual ::ca::application * get_app() const;

      string get_license_id()
      {
         return m_strLicense;
      }

      virtual void get_time(timeval *p);
      virtual void set_env_var(const string & var,const string & value);
      virtual unsigned long get_thread_id();

      virtual void message_window_message_handler(gen::signal_object * pobj);

      virtual bool on_install();
      virtual bool on_uninstall();
      virtual bool on_run_install();
      virtual bool on_run_uninstall();

      virtual void request_application(::ca2::application_request * prequest);


      DECL_GEN_SIGNAL(_001OnApplicationRequest)

   };

   inline CLASS_DECL_ca application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca


#include "ca/ca_font.h"