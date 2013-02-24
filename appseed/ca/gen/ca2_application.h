#pragma once


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


   class CLASS_DECL_ca application :
      virtual public ::gen::application
   {
   public:


      ::calculator::calculator                                                                * m_pcalculator;
      ::sockets::sockets                                                                      * m_psockets;
      ::colorertake5::colorertake5                                                            * m_pcolorertake5;


      ::collection::string_map < string_to_string_map *, string_to_string_map * >               m_stringtablemap;
      ::collection::string_map < string_to_string_map *, string_to_string_map * >               m_stringtablemapStd;
      manual_reset_event *                                                                      m_peventReady;


      //string                                                                                  m_strLicense;
      bool                                                                                      m_bLicense;
      string                                                                                    m_strBaseSupportId;
      collection::map < int32_t, int32_t, bool, bool > *                                        m_pmapKeyPressed;


      string                                                                                    m_strRoot;
      string                                                                                    m_strDomain;
      string                                                                                    m_strLocale;
      string                                                                                    m_strSchema;




      const string OAUTHLIB_CONSUMERKEY_KEY;
      const string OAUTHLIB_CALLBACK_KEY;
      const string OAUTHLIB_VERSION_KEY;
      const string OAUTHLIB_SIGNATUREMETHOD_KEY;
      const string OAUTHLIB_SIGNATURE_KEY;
      const string OAUTHLIB_TIMESTAMP_KEY;
      const string OAUTHLIB_NONCE_KEY;
      const string OAUTHLIB_TOKEN_KEY;
      const string OAUTHLIB_TOKENSECRET_KEY;
      const string OAUTHLIB_VERIFIER_KEY;
      const string OAUTHLIB_SCREENNAME_KEY;


      const string OAUTHLIB_TWITTER_REQUEST_TOKEN_URL;
      const string OAUTHLIB_TWITTER_AUTHORIZE_URL;
      const string OAUTHLIB_TWITTER_ACCESS_TOKEN_URL;

      /* Constants */
      const string TWIT_COLON;
      const char TWIT_EOS;

      /* Miscellaneous data used to build twitter URLs*/
      const string TWIT_SEARCHQUERYSTRING;      
      const string TWIT_SCREENNAME;
      const string TWIT_USERID;
      const string TWIT_EXTENSIONFORMAT;
      const string TWIT_TARGETSCREENNAME;
      const string TWIT_TARGETUSERID;

      /* Search URLs */
      const string TWIT_SEARCH_URL;

      /* Status URLs */
      const string TWIT_STATUSUPDATE_URL;
      const string TWIT_STATUSSHOW_URL;
      const string TWIT_STATUDESTROY_URL;

      /* Timeline URLs */
      const string TWIT_PUBLIC_TIMELINE_URL;
      const string TWIT_FEATURED_USERS_URL;
      const string TWIT_FRIENDS_TIMELINE_URL;
      const string TWIT_MENTIONS_URL;
      const string TWIT_USERTIMELINE_URL;

      /* Users URLs */
      const string TWIT_SHOWUSERS_URL;
      const string TWIT_SHOWFRIENDS_URL;
      const string TWIT_SHOWFOLLOWERS_URL;

      /* Direct messages URLs */
      const string TWIT_DIRECTMESSAGES_URL;
      const string TWIT_DIRECTMESSAGENEW_URL;
      const string TWIT_DIRECTMESSAGESSENT_URL;
      const string TWIT_DIRECTMESSAGEDESTROY_URL;

      /* Friendships URLs */
      const string TWIT_FRIENDSHIPSCREATE_URL;
      const string TWIT_FRIENDSHIPSDESTROY_URL;
      const string TWIT_FRIENDSHIPSSHOW_URL;

      /* Social graphs URLs */
      const string TWIT_FRIENDSIDS_URL;
      const string TWIT_FOLLOWERSIDS_URL;

      /* Account URLs */
      const string TWIT_ACCOUNTRATELIMIT_URL;

      /* Favorites URLs */
      const string TWIT_FAVORITESGET_URL;
      const string TWIT_FAVORITECREATE_URL;
      const string TWIT_FAVORITEDESTROY_URL;

      /* Block URLs */
      const string TWIT_BLOCKSCREATE_URL;
      const string TWIT_BLOCKSDESTROY_URL;
    
      /* Saved Search URLs */
      const string TWIT_SAVEDSEARCHGET_URL;
      const string TWIT_SAVEDSEARCHSHOW_URL;
      const string TWIT_SAVEDSEARCHCREATE_URL;
      const string TWIT_SAVEDSEARCHDESTROY_URL;

      /* Trends URLs */
      const string TWIT_TRENDS_URL;
      const string TWIT_TRENDSDAILY_URL;
      const string TWIT_TRENDSCURRENT_URL;
      const string TWIT_TRENDSWEEKLY_URL;
      const string TWIT_TRENDSAVAILABLE_URL;

      application();
      virtual ~application();


      virtual void install_message_handling(::gen::message::dispatch * pdispatch);

      virtual int32_t run();

      virtual string get_locale();
      virtual string get_schema();
      virtual string get_locale_schema_dir(const string & strLocale, const string & strSchema);
      virtual string get_locale_schema_dir(const string & strLocale);
      virtual string get_locale_schema_dir();

      virtual void EnableShellOpen();

      virtual bool open_link(const string & strLink, const string & pszTarget = "");




      virtual void set_locale(const string & lpcsz, bool bUser);
      virtual void set_schema(const string & lpcsz, bool bUser);
      virtual void on_set_locale(const string & lpcsz, bool bUser);
      virtual void on_set_schema(const string & lpcsz, bool bUser);


      virtual ::fontopus::user * create_current_user();


      virtual bool initialize1();
      virtual bool initialize();
      virtual bool finalize();

      virtual void _001CloseApplication();



      virtual bool start_application(bool bSynch, ::ca::application_bias * pbias);


      inline ::calculator::calculator           & calculator      () { return *m_pcalculator    ; }
      inline ::sockets::sockets                 & sockets         () { return *m_psockets       ; }
      inline ::colorertake5::colorertake5       & colorertake5    () { return *m_pcolorertake5  ; }


      //virtual string get_current_user_login();

      virtual string load_string(id id);
      virtual bool load_string(string & str, id id);
      bool load_cached_string(string & str, id id, bool bLoadStringTable);
      bool load_cached_string_by_id(string & str, id id, const string & pszFallbackValue, bool bLoadStringTable);
      void load_string_table(const string & pszApp, const string & pszId);

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);

      virtual bool base_support();

      virtual string message_box(const string & pszMatter, gen::property_set & propertyset);


      virtual void load_string_table();

      virtual ::user::interaction * uie_from_point(point pt);

      virtual bool bergedge_start();

      void process(machine_event_data * pdata);

      virtual void pre_translate_message(gen::signal_object * pobj);

      ::mutex * get_local_mutex();
      ::mutex * get_global_mutex();

      virtual ::ca::application * get_app() const;

      virtual string get_license_id();

#ifndef METROWIN
      virtual void get_time(timeval *p);
#endif
      virtual void set_env_var(const string & var,const string & value);
      virtual uint32_t get_thread_id();

      virtual void message_window_message_handler(gen::signal_object * pobj);

      virtual bool on_install();
      virtual bool on_uninstall();
      virtual bool on_run_install();
      virtual bool on_run_uninstall();

      DECL_GEN_SIGNAL(_001OnApplicationRequest)

      virtual bool is_key_pressed(int32_t iKey);
      virtual void set_key_pressed(int32_t iKey, bool bPressed);


      virtual bool is_running();

      virtual int32_t exit_instance();

      DECL_GEN_SIGNAL(on_application_signal);


   };


} // namespace ca



#include "ca/ca/ca_font.h"



