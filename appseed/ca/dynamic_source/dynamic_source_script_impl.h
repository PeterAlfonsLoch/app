#pragma once


namespace webserver
{


/*class ui_menu;*/
   class ui_str;
   class checkimage;
   class ui_redir;


} // namespace webserver


namespace mail
{


   class pop3;


} // namespace mail



namespace dynamic_source
{

   class exit_exception
   {
   public:
      exit_exception(int iCode);
      int m_iCode;
   };


   class CLASS_DECL_ca script_impl :
      public script_interface
   {
   public:


      GeoIPRecord *                       m_pgeoiprecordClient;
      string2a                            m_str2aScript;
      stringa                             m_straUserDir;


      bool m_bSession;
      script *                            m_pscript;
      string_to_string_map                m_strmap;
      gen::property_set *                 m_ppropertysetVar;
      gen::property_set *                 m_ppropertysetSession;
      mutex *                             m_pmutexSession;
      var                                 m_varRet;
      script_impl *                       m_pinstanceParent;
      script_impl *                       m_pinstanceMain;
      script_manager *                    m_pmanager;
      string                              m_strImageWebSite;
      string                              m_strCssWebSite;
      string                              m_strFileWebSite;
      string                              m_strCa2VFallbackWebSite;
      string                              m_strCa2OpenWebSite;

      ::webserver::fun::fun *             m_pfun;
      comparable_array < ptr * >          m_ptra;
      ::webserver::fontopus_database *    m_pmusicdb;
      ::webserver::fontopus_database *    m_pmusicsedb;
      ::webserver::fontopus_database *    m_pnetnodedb;
      ::webserver::fontopus_database *    m_padmindb;
      ::webserver::secure *               m_psecure;
      ::webserver::music::music *         m_pmusic;
      ::webserver::cynce_database *       m_pcyncedb;
      ::webserver::cynce *                m_pcynce;
      ::webserver::user *                 m_pui;
      ::webserver::wb *                   m_pwb;

      ::dynamic_source::profiler *        m_pprofiler;

      bool                                m_bOnTopicInclude;

      int                                 m_iDebug;

      array_app_alloc < ::http::memory_file, ::http::memory_file &> m_memoryfileaPrint;

      ::netnode::socket *                 m_pnetnodesocket;
      ::webserver::ui_str *               m_puistr;
      ::http::memory_file                 m_memoryfileFallback;
      ::webserver::checkimage *           m_pcheckimage;





      // Implementation
      script_impl(script * pscript);
      virtual ~script_impl();


      template < class singleton >
      singleton & lib ()
      {
         string strPropName = "netnode::script::singleton::";
#ifdef WINDOWS
         strPropName += typeid(singleton).raw_name();
#else
         strPropName += typeid(singleton).name();
#endif
         singleton * p = gprop(strPropName).ca2 < singleton >();
         if(p != NULL)
            return *p;
         string strName = typeid(singleton).name();
         string strPath = strName;
         strPath.replace("::", "/");
         strPath.replace("_", "/");
         p = new singleton;
         gprop(strPropName) = p;
         return *p;
      }



      virtual void keep(ptr * pptr);
      virtual void unkeep(ptr * pptr);

      gen::property & request_uri();

      void session_ensure();

      webserver::checkimage & checkimage();


      netnode::socket & netnode();


      void root_init();

      class webserver::ui_redir & uiredir();

      virtual void ob_start();
      virtual primitive::memory ob_get_clean();


      string pstr(id pszTopic, id pszLocale = id(), id pszStyle = id());
      string pstr(id pszTopic, gen::property_set & set, id pszLocale = id(), id pszStyle = id());
      void pstr_set(id pszTopic, id pszLocale, id pszStyle, const char * psz);


      var http_accept_language(const char * psz = NULL);
      string normalize_locale(const char * psz = NULL);

      bool isset(var & var);
      bool isset(gen::property & prop);
      bool is_null(var & var);
      bool is_null(gen::property & prop);

      virtual string real_path(const char * psz);
      virtual string real_path(const char * pszBase, const char * psz);
      virtual string system_path(const char * psz);

      virtual string langstr(const char * pszKey);
      virtual string langstr2(const char * pszKey);
      virtual void print_langstr(const char * pszKey);
      virtual void set_langstr(const char * pszKey, const char * pszValue);


      virtual string current_url();

      virtual string urlencode(const char * psz);
      virtual string urldecode(const char * psz);
      virtual string htmlspecialchars(const char * psz);
      virtual string htmlentities(const char * psz);

      virtual script_manager * get_manager();

      void dinit();
      void dprint(const char *);
      void dprint_r(var var);
      void dfinish();

      // profiling
      virtual __int64 get_first_time();
      virtual void prof_enter(const char * psz);
      virtual void prof_leave(const char * psz);
      virtual void prof_display();
      virtual void until_here();
      virtual class profiler * profiler();


      virtual gen::property & gprop(const char * pszKey);

      string set_cookie(
         const char * pszKey,
         var var,
         int iExpire = 0,
         const char * pszPath = NULL,
         const char * pszDomain = NULL,
         bool bSecure = false);


      gen::property     & get(const char * pszKey);
      gen::property     & post(const char * pszKey);
      http::cookie      & cookie(const char * pszKey);
      gen::property     & request(const char * pszKey);
      gen::relation_set & geta();
      gen::relation_set & posta();
      http::cookies     & cookies();
      gen::relation_set & requesta();

      void set_session_value(const char * psz, var value);
      var get_session_value(const char * psz);

      //gen::property_set & sessiona();
      gen::property_set & inattra();

      using script_interface::this_url;
      string this_url();

      virtual string session_id(const char * pszId = NULL);

      gen::property & inheader(const char * psz);
      gen::property & outheader(const char * psz);

      gen::property & inattr(const char * psz);
      gen::property & outattr(const char * psz);


      virtual void hand_root();
      virtual void hand_sec();
      virtual void hand_img();
      virtual void hand_err();
      virtual void hand_krftimg();
      virtual void hand_karaoke();
      virtual void hand_cifras();
      virtual void hand_letras();
      virtual void hand_extension();

      void mbimage_outputImage(
         var text,
         var size = "b",
         var bk = "mb");
      void mbimage_rectImage(var w, var h);
      COLORREF color(var c);

      var emphasize_text(var textArg, var emphasizeArg);

      void echo(const char * lpcsz);

      // for printing "static text" (from html)
      void ds_print(const char * lpcsz);

      void raw_print(const char * lpcsz);

      virtual void print_r(var var);
      virtual void print(const char * lpcsz);
      virtual void printf(const char * lpcsz, ...);
      virtual void printstr(const char * lpcsz, ...);
      virtual void print_url(const char * pszUrl);

      bool read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea = NULL, const char * pszContentType = NULL);

      virtual int exit(int iExitCode);


      bool main_initialize();
      bool main_finalize();

      bool session_open(const char * pszSavePath, const char * pszSessionName);
      bool session_close();
      bool session_read(const char * pszId, gen::property_set & set);
      bool session_write(const char * pszId, gen::property_set & set);
      bool session_destroy(const char * pszId) ;

      /*********************************************
      * WARNING - You will need to implement some *
      * sort of garbage collection routine here.  *
      *********************************************/
      bool session_gc(int maxlifetime);


      void menuleft_printVert001(::webserver::ui_menu * pmenu, int iPanelIndex);

      //string use_style_calc_initial_css_modifier_prefix();

      bool defer_expand_file(const char * lpcszPath);
      string defer_expanded_file_string(const char * lpcszPath);
      var include(const char * lpcsz, bool bRoot = false);
      void launch(const char * lpcsz);
//      void edgify(int iEdge, ::userbase::document_template * ptemplate, bool bMakeVisible);
  //    void edgify_app(int iEdge, ::ca::type_info prtcApp, bool bMakeVisible);

      virtual void run();


      virtual string sys_get_include_path(const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept = NULL);
      virtual string sys_get_base_path(const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept = NULL);
      virtual string sys_get_subdomain_path(const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept = NULL);
      virtual string named_sys_get_include_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept = NULL);
      virtual string named_sys_get_base_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept = NULL);
      virtual string named_sys_get_subdomain_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept = NULL);


      void script_start();
      void script_step();
      void script_end();
      bool script_right();

      virtual string ui_exuri();
      virtual string a_go1(var var);


      void ui_nav_printOut5(stringa & straLink, stringa & straTitle);
      void ui_nav_printOut3(stringa & straLink, stringa & straTitle);
      void ui_nav_printOut2(stringa & straLink, stringa & straTitle);
      void ui_nav_printOut1(stringa & straLink, stringa & straTitle);

      virtual string ui_redir(const char * pszLang, const char * pszStyle, const char * pszExUri = "", const char * pszRoot = "");
      virtual void ui_redir_add(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszTarget);

      void load_stringtable(const char * psz);

      string eval(const char * pszText);

      virtual ::webserver::fun::fun & fun();
      virtual ::webserver::fontopus_database & musicdb();
      virtual ::webserver::fontopus_database & musicdb_se();
      virtual ::webserver::fontopus_database & netnodedb();
      virtual ::webserver::fontopus_database & admindb();
      virtual ::webserver::secure & secure();
      virtual ::webserver::music::music & music();
      virtual ::webserver::cynce_database & cyncedb();
      virtual ::webserver::cynce & cynce();
      virtual ::webserver::user & user();
      virtual ::webserver::wb & wb();

      string uri_set_var(const char * pszQuery, const char * pszKey, var var);

      virtual string get_current_url();

      virtual int ca2_fetch_mode(int iMode = -1);

      virtual int64_t strtotime(const char * psz, time_t time);
      virtual int64_t strtotime(const char * psz);
      virtual int64_t str_context_strtotime(const char * psz, time_t time);
      virtual int64_t str_context_strtotime(const char * psz);
      virtual string strftime(const char * psz, time_t time);
      virtual string strftime(const char * psz);
      virtual var rand(var start, var end);




      virtual void use_style_get_accepta(gen::property_set & set);
      virtual string use_style_get_default();
      virtual string use_style_calc_initial_css_modifier_prefix();
      virtual void use_style_set_style(const char * pszId);
      virtual string use_style_get_path_prefix(const char * pszId);
      virtual string use_style_get1();

      virtual void header(const char * pszHeader);

      void simple_file_server(const char * psz, const char * psz2 = NULL);


      string ui_url(const char * pszTopic, const char * pszStyle = NULL);


      void cla_sel1(const char * pszSection, const char * pszItem);

      string ca2_get_build(const char * pszVersion);
      string ca2_get_subversion_revision(const char * pszVersion);
      string ca2_format_build(const char * pszVersion);


      void ensure_ssl();

      void echo_spa(const char * psz, const char * pszBuild = NULL);
      string spa_url(const char * psz, const char * pszBuild = NULL);
      virtual string spa_calc_best_host();
      virtual GeoIPRecord * get_client_geopip_record();


      virtual void image_png(::ca::bitmap_sp pbitmap);

      bool is_common_dir(const char * psz);

      string locale_from_request_v1(const char * psz);

      bool locale_is_eu(const char * pszLocale);
      bool locale_is_asia(const char * pszLocale);
      bool locale_is_es(const char * pszLocale);
      bool locale_is_de(const char * pszLocale);

      bool locale_is_south_america(const char * pszLocale);
      bool locale_is_north_america(const char * pszLocale);
      bool locale_is_central_america(const char * pszLocale);
      bool locale_is_latin_america(const char * pszLocale);

      virtual var explode(const char * pszDelimiter, const char * psz);
      virtual string implode(const char * pszGlue, const var & var);
      virtual string implode(const char * pszGlue, const stringa & stra);

      virtual bool in_array(const var & varElement, const var & varArray);
      using script_interface::array_unshift;
      virtual void array_unshift(var & varArray, const var varElement);

      virtual ::count count(var var);

      var array(
         var var01 = ::var(::var::e_type::type_empty_argument),
         var var02 = ::var(::var::e_type::type_empty_argument),
         var var03 = ::var(::var::e_type::type_empty_argument),
         var var04 = ::var(::var::e_type::type_empty_argument),
         var var05 = ::var(::var::e_type::type_empty_argument),
         var var06 = ::var(::var::e_type::type_empty_argument),
         var var07 = ::var(::var::e_type::type_empty_argument),
         var var08 = ::var(::var::e_type::type_empty_argument),
         var var09 = ::var(::var::e_type::type_empty_argument),
         var var10 = ::var(::var::e_type::type_empty_argument),
         var var11 = ::var(::var::e_type::type_empty_argument),
         var var12 = ::var(::var::e_type::type_empty_argument),
         var var13 = ::var(::var::e_type::type_empty_argument),
         var var14 = ::var(::var::e_type::type_empty_argument),
         var var15 = ::var(::var::e_type::type_empty_argument),
         var var16 = ::var(::var::e_type::type_empty_argument),
         var var17 = ::var(::var::e_type::type_empty_argument),
         var var18 = ::var(::var::e_type::type_empty_argument),
         var var19 = ::var(::var::e_type::type_empty_argument),
         var var20 = ::var(::var::e_type::type_empty_argument),
         var var21 = ::var(::var::e_type::type_empty_argument),
         var var22 = ::var(::var::e_type::type_empty_argument),
         var var23 = ::var(::var::e_type::type_empty_argument),
         var var24 = ::var(::var::e_type::type_empty_argument),
         var var25 = ::var(::var::e_type::type_empty_argument));

      virtual bool is_array(var var);

      virtual var array_merge(
         var var01 = ::var(::var::e_type::type_empty_argument),
         var var02 = ::var(::var::e_type::type_empty_argument),
         var var03 = ::var(::var::e_type::type_empty_argument),
         var var04 = ::var(::var::e_type::type_empty_argument),
         var var05 = ::var(::var::e_type::type_empty_argument),
         var var06 = ::var(::var::e_type::type_empty_argument),
         var var07 = ::var(::var::e_type::type_empty_argument),
         var var08 = ::var(::var::e_type::type_empty_argument),
         var var09 = ::var(::var::e_type::type_empty_argument),
         var var10 = ::var(::var::e_type::type_empty_argument),
         var var11 = ::var(::var::e_type::type_empty_argument),
         var var12 = ::var(::var::e_type::type_empty_argument),
         var var13 = ::var(::var::e_type::type_empty_argument),
         var var14 = ::var(::var::e_type::type_empty_argument),
         var var15 = ::var(::var::e_type::type_empty_argument),
         var var16 = ::var(::var::e_type::type_empty_argument),
         var var17 = ::var(::var::e_type::type_empty_argument),
         var var18 = ::var(::var::e_type::type_empty_argument),
         var var19 = ::var(::var::e_type::type_empty_argument),
         var var20 = ::var(::var::e_type::type_empty_argument),
         var var21 = ::var(::var::e_type::type_empty_argument),
         var var22 = ::var(::var::e_type::type_empty_argument),
         var var23 = ::var(::var::e_type::type_empty_argument),
         var var24 = ::var(::var::e_type::type_empty_argument),
         var var25 = ::var(::var::e_type::type_empty_argument));

      virtual void echo_simage(var param_view);
      virtual string simage(var param_view);
      virtual void simage_add_accepta(::webserver::simage_accepta * paccepta);
      virtual string simage_relative(var param_view);

      virtual bool net_hostname_is_spider(const char * hostname, const char * useragent = NULL);
      virtual void add_spider_match_host(const char * hostname, const char * useragent = NULL);

      virtual string query_ca2(const char * pszQuery);
      virtual void ca2_query_date(stringa & straResp, class time & time, const char * pszDateTime, const char * pszQuery);
      virtual string ca2_html_fluidcode(const char * pszFreeText); // output is linked html

      virtual script_interface & main();
      virtual ::user::str_context * str_context();

      virtual void print_email_body(::mail::pop3 * ppop3);
      virtual void print_plain_text_email_body(::mail::pop3 * ppop3);

      virtual ::http::file & output_file();


      virtual void filter_user_presence_status(const char * pszUserId);

      virtual bool is_licensed(const char * pszLicense, const char * pszUserId);

      virtual string web_map(const char * psz);

      virtual bool is_site_user(var varSite, var varUser);
      virtual bool is_site_user(var varSite);

      virtual string    low_fs_file_path        (const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, gen::property_set set = gen::property_set());
      virtual bool      low_fs_read             (const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension);
      virtual __int64   low_fs_map              (const char * pszDir);
      virtual bool      low_fs_map_file         (const char * pszPath);
      virtual bool      low_fs_license          (const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension);
      virtual bool      low_fs_is_licensed      (const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension);

      virtual bool      low_fs_read             (const char * user, __int64 iFolder, const char * pszName);
      virtual bool      low_fs_write            (const char * user, __int64 iFolder, const char * pszName);
      virtual bool      low_fs_write            (const char * user, __int64 iFolder, const char * pszName, ::ex1::file * pfile, const char * pszContentType);
      virtual bool      low_fs_add_user_file    (const char * user, __int64 iFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char * pszName, bool bOverwrite);
      virtual __int64   low_fs_add_user_dir     (const char * user, __int64 iFolder, const char * pszName);
      virtual void      low_fs_ls_dir           (const char * user, __int64 iFolder, int64_array & ia, stringa & stra);
      virtual void      low_fs_ls_file          (const char * user, __int64 iFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName);

      virtual bool      low_folder              (string & strUser, __int64 & iFolder, const char * pszFolder);

      virtual bool      fs_dir_mk               (const char * pszFolder);


      virtual string datetime_get_month_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);
      virtual string datetime_get_month_short_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);
      virtual string datetime_get_weekday_short_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);
      virtual string datetime_get_weekday_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);

      virtual int datetime_get_month_day_count(int year, int month);
      // 0 is Sunday
      virtual string datetime_get_weekday(int year, int month, int day);
      virtual class time datetime_get_timestamp(int year, int  month,  int day);
      virtual string datetime_getGMTDateTime();
      virtual string datetime_formatDateTime(class time t);
      virtual class time datetime_getTimestamp();
      virtual __int64 datetime_InternationalToUnixMillis(const char * date);
      virtual string datetime_getToday();
      virtual class time datetime_strtotime(const char * psz);
      virtual class time datetime_strtotime(const char * psz, class time t);

      virtual void fontopus_ds_url_update_named();



   };


} // namespace dynamic_source


