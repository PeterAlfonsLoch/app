#pragma once


namespace dynamic_source
{


   class CLASS_DECL_ca script_composite :
      virtual public script_interface
   {
   public:


      script_interface * m_pinterface;


      script_composite();
      virtual ~script_composite();



      template < class singleton >
      singleton & ca2 ()
      {
         return m_pinterface->ca2 < singleton >();
      }


      virtual void keep(ptr * pptr);
      virtual void unkeep(ptr * pptr);


      virtual void dinit();
      virtual void dprint(const char *);
      virtual void dprint_r(var var);
      virtual void dfinish();


      // profiling

      virtual __int64 get_first_time();
      virtual void prof_enter(const char * psz);
      virtual void prof_leave(const char * psz);
      virtual void until_here();
      virtual class profiler * profiler();


      string set_cookie(
         const char * pszKey,
         var var,
         int iExpire = 0,
         const char * pszPath = NULL, 
         const char * pszDomain = NULL,
         bool bSecure = false);

      virtual gen::property & gprop(const char * pszKey);

      gen::property & get(const char * pszKey);
      gen::property & post(const char * pszKey);
      http::cookie      & cookie(const char * pszKey);
      gen::property & request(const char * pszKey);
      //gen::property & session(const char * pszKey);
      gen::relation_set & geta();
      gen::relation_set & posta();
      http::cookies     & cookies();
      gen::relation_set & requesta();

      void set_session_value(const char * psz, var value);
      var get_session_value(const char * psz);

      //gen::property_set & sessiona();
      gen::property_set & inattra();

      using script_interface::this_url;
      virtual string this_url();

      virtual string session_id(const char * pszId = NULL);

      gen::property & inheader(const char * psz);
      gen::property & outheader(const char * psz);

      gen::property & inattr(const char * psz);
      gen::property & outattr(const char * psz);


      virtual void get_output(string & strHeader, http::memory_file & memfile);

      virtual void hand_root();
      virtual void hand_karaoke();
      virtual void hand_cifras();
      virtual void hand_letras();

      virtual void ds_print(const char * lpcsz);
      virtual void raw_print(const char * lpcsz);

      virtual void print_r(var var);
      virtual void print(const char * lpcsz);
      virtual bool read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea = NULL, const char * pszContentType = NULL);

      virtual var include(const char * lpcsz, bool bRoot = false);
      virtual void launch(const char * lpcsz);
//      virtual void edgify(int iEdge, ::userbase::document_template * ptemplate, bool bMakeVisible);
  //    virtual void edgify_app(int iEdge, ::ca::type_info prtcApp, bool bMakeVisible);

      virtual string real_path(const char * psz);
      virtual string system_path(const char * psz);

      string pstr(id pszTopic, id pszLocale = id(), id pszStyle = id());
      string pstr(id pszTopic, gen::property_set & set, id pszLocale = id(), id pszStyle = id());

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

      virtual netnode::socket & netnode();

      virtual void run();

      virtual string sys_get_include_path(const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept = NULL);
      virtual string sys_get_base_path(const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept = NULL);
      virtual string sys_get_subdomain_path(const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept = NULL);
      virtual string named_sys_get_include_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept = NULL);
      virtual string named_sys_get_base_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept = NULL);
      virtual string named_sys_get_subdomain_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept = NULL);

      virtual void script_start();
      virtual void script_step();
      virtual void script_end();
      virtual bool script_right();

      virtual string ui_exuri();



      virtual void ui_nav_printOut5(stringa & straLink, stringa & straTitle);
      virtual void ui_nav_printOut3(stringa & straLink, stringa & straTitle);
      virtual void ui_nav_printOut2(stringa & straLink, stringa & straTitle);
      virtual void ui_nav_printOut1(stringa & straLink, stringa & straTitle);

      virtual string ui_redir(const char * pszLang, const char * pszStyle, const char * pszExUri = "", const char * pszRoot = "");
      virtual void ui_redir_add(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszTarget);

      virtual ::webserver::fun::fun & fun();
      virtual ::webserver::fontopus_database & musicdb();
      virtual ::webserver::fontopus_database & musicdb_se();
      virtual ::webserver::fontopus_database & admindb();
      virtual ::webserver::secure & secure();
      virtual ::webserver::music::music & music();
      virtual ::webserver::cynce_database & cyncedb();
      virtual ::webserver::cynce & cynce();
      virtual ::webserver::user & user();
      virtual ::webserver::wb & wb();

      string uri_set_var(const char * pszQuery, const char * pszKey, var var);

      virtual string eval(const char * pszText);

      virtual string get_current_url();

      virtual int ca2_fetch_mode(int iMode = -1);

      virtual int64_t strtotime(const char * psz, time_t time);
      virtual int64_t strtotime(const char * psz);
      virtual string strftime(const char * psz, time_t time);
      virtual string strftime(const char * psz);
      virtual var rand(var start, var end);


      virtual int exit(int iExitCode);

      virtual void header(const char * pszHeader);

      virtual string ui_url(const char * pszTopic, const char * pszStyle = NULL);

      virtual void cla_sel1(const char * section, const char * item);


      virtual string spa_calc_best_host();
      virtual GeoIPRecord * get_client_geopip_record();

      virtual void image_png(::ca::bitmap_sp pbitmap);

      virtual var explode(const char * pszDelimiter, const char * psz);
      virtual string implode(const char * pszDelimiter, const var & var);
      virtual string implode(const char * pszDelimiter, const stringa & var);

      virtual bool in_array(const var & varElement, const var & varArray);
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
      virtual void simage_add_accepta(webserver::simage_accepta * paccepta);
      virtual string simage_relative(var param_view) ;

      virtual bool net_hostname_is_spider(const char * hostname, const char * useragent = NULL);
      virtual void add_spider_match_host(const char * hostname, const char * useragent = NULL);

      virtual script_interface & main();
      virtual ::user::str_context * str_context();

      virtual ::http::file & output_file();


      virtual void filter_user_presence_status(const char * pszUserId);

      virtual bool is_licensed(const char * pszLicense, const char * pszUserId);

      virtual void menuleft_printVert001(::webserver::ui_menu * pmenu, int iPanelIndex);

      virtual string web_map(const char * psz);

      virtual bool is_site_user(var varSite, var varUser);
      virtual bool is_site_user(var varSite);

      virtual string    low_fs_file_path        (const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, gen::property_set set =  gen::property_set());
      virtual bool      low_fs_read             (const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension);
      virtual __int64   low_fs_map              (const char * pszDir);
      virtual bool      low_fs_map_file         (const char * pszPath);
      virtual bool      low_fs_license          (const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension);
      virtual bool      low_fs_is_licensed      (const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension);

      virtual bool      low_fs_read             (const char * user, __int64 iFolder, const char * pszName);
      virtual bool      low_fs_add_user_file    (const char * user, __int64 iFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char * pszName, bool bOverwrite);
      virtual __int64   low_fs_add_user_dir     (const char * user, __int64 iFolder, const char * pszName);
      virtual void      low_fs_ls_dir           (const char * user, __int64 iFolder, int64_array & ia, stringa & stra);
      virtual void      low_fs_ls_file          (const char * user, __int64 iFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName);

      virtual bool      low_folder(string & strUser, __int64 & iFolder, const char * pszFolder);

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

      


   };


} // namespace dynamic_source


