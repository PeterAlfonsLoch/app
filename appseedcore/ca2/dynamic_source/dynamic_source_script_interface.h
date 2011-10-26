#pragma once


namespace webserver
{


   namespace music
   {


      class music;


   } // namespace music


   class user;
   class wb;
   class simage_accepta;
   class socket;
   class ui_menu;
   class cynce_database;
   class fontopus_database;
   class secure;
   class cynce;


   namespace fun
   {


      class fun;


   } // namespace fun


} // namespace netnode


namespace dynamic_source
{


   class ptr;
   class script_manager;
   class profiler;


   class CLASS_DECL_ca script_interface :
      virtual public ::html::file
   {
   public:
      script_interface();
      virtual ~script_interface();

      virtual void keep(ptr * pptr) = 0;
      virtual void unkeep(ptr * pptr) = 0;

      virtual void dinit();
      virtual void dprint(const char *);
      virtual void dprint_r(var var) = 0;
      virtual void dfinish();

      // profiling

      virtual __int64 get_first_time() = 0;
      virtual void prof_enter(const char * psz) = 0;
      virtual void prof_leave(const char * psz) = 0;
      virtual void until_here() = 0;
      virtual class profiler * profiler() = 0;


      virtual string & gstr(const char * pszKey);
      virtual gen::property & gprop(const char * pszKey);
      bool isset(gen::property & prop);

      virtual string set_cookie(
         const char * pszKey,
         var var,
         int iExpire = 0,
         const char * pszPath = NULL, 
         const char * pszDomain = NULL,
         bool bSecure = false) = 0;

      virtual gen::property & get(const char * pszKey) = 0;
      virtual gen::property & post(const char * pszKey) = 0;
      virtual http::cookie      & cookie(const char * pszKey) = 0;
      using ::html::file::request;
      virtual gen::property & request(const char * pszKey) = 0;
      virtual gen::property & session(const char * pszKey) = 0;
      virtual gen::relation_set & geta() = 0;
      virtual gen::relation_set & posta() = 0;
      virtual http::cookies     & cookies() = 0;
      virtual gen::relation_set & requesta() = 0;
      virtual gen::property_set & sessiona() = 0;
      virtual gen::property_set & inattra() = 0;

      virtual string session_id(const char * pszId = NULL) = 0;

      virtual gen::property & inheader(const char * psz) = 0;
      virtual gen::property & outheader(const char * psz) = 0;

      virtual gen::property & inattr(const char * psz) = 0;
      virtual gen::property & outattr(const char * psz) = 0;


      virtual string this_url() = 0;
      virtual string this_url(const char * pszKey, var var);

      virtual void get_output(string & strHeader, http::memory_file & memfile);

      virtual void hand_root();
      virtual void hand_karaoke() = 0;
      virtual void hand_cifras() = 0;
      virtual void hand_letras() = 0;


      virtual netnode::socket & netnode();

      virtual void ds_print(const char * lpcsz) = 0;
      virtual void raw_print(const char * lpcsz) = 0;

      virtual void print_r(var var) = 0;
      virtual void print(const char * lpcsz);
      virtual void printf(const char * lpcsz, ...);
      virtual void printstr(const char * lpcsz, ...);
      virtual bool read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea = NULL, const char * pszContentType = NULL);

      virtual var include(const char * lpcsz);
      virtual void launch(const char * lpcsz);
      virtual void edgify(int iEdge, ::userbase::document_template * ptemplate, bool bMakeVisible);
      virtual void edgify_app(int iEdge, ::ca::type_info prtcApp, bool bMakeVisible);

      virtual string real_path(const char * psz) = 0;
      virtual string system_path(const char * psz) = 0;

      virtual string pstr(const char * pszTopic, const char * pszLocale = NULL, const char * pszStyle = NULL) = 0;
      virtual string pstr(const char * pszTopic, gen::property_set & set, const char * pszLocale = NULL, const char * pszStyle = NULL) = 0;

      virtual string langstr(const char * pszKey) = 0;
      virtual string langstr2(const char * pszKey) = 0;
      virtual void print_langstr(const char * pszKey) = 0;
      virtual void set_langstr(const char * pszKey, const char * pszValue) = 0;

      virtual string current_url() = 0;

      virtual string urlencode(const char * psz) = 0;
      virtual string urldecode(const char * psz) = 0;
      virtual string htmlspecialchars(const char * psz) = 0;
      virtual string htmlentities(const char * psz) = 0;

      virtual script_manager * get_manager() = 0;

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

      virtual ::webserver::fun::fun & fun() = 0;
      virtual ::webserver::fontopus_database & musicdb() = 0;
      virtual ::webserver::fontopus_database & musicdb_se() = 0;
      virtual ::webserver::fontopus_database & admindb() = 0;
      virtual ::webserver::secure & secure() = 0;
      virtual ::webserver::music::music & music() = 0;
      virtual ::webserver::cynce_database & cyncedb() = 0;
      virtual ::webserver::cynce & cynce() = 0;
      virtual ::webserver::user & user() = 0;
      virtual ::webserver::wb & wb() = 0;

      virtual string uri_set_var(const char * pszQuery, const char * pszKey, var var) = 0;

      virtual string eval(const char * pszText) = 0;

      virtual string get_current_url() = 0;

      virtual int ca2_fetch_mode(int iMode = -1) = 0;

      virtual int64_t strtotime(const char * psz, time_t time) = 0;
      virtual int64_t strtotime(const char * psz) = 0;
      virtual string strftime(const char * psz, time_t time) = 0;
      virtual string strftime(const char * psz) = 0;
      virtual var rand(var start, var end) = 0;

      virtual int exit(int iExitCode) = 0;

      virtual void header(const char * pszHeader) = 0;

      virtual string ui_url(const char * pszTopic, const char * pszStyle = NULL) = 0;

      virtual void cla_sel1(const char * pszSection, const char * pszItem) = 0;



      virtual string spa_calc_best_host() = 0;
      virtual GeoIPRecord * get_client_geopip_record() = 0;

      virtual void image_png(::ca::bitmap_sp pbitmap) = 0;

      virtual var explode(const char * pszDelimiter, const char * psz) = 0;
      virtual string implode(const char * pszDelimiter, const var & var) = 0;

      virtual bool in_array(const var & varElement, const var & varArray) = 0;
      virtual void array_unshift(gen::property & varArray, const var varElement);
      virtual void array_unshift(var & varArray, const var varElement) = 0;

      virtual int count(var var) = 0;

      virtual var array(
         var var01 = gen::g_emptyargumentconst,
         var var02 = gen::g_emptyargumentconst,
         var var03 = gen::g_emptyargumentconst,
         var var04 = gen::g_emptyargumentconst,
         var var05 = gen::g_emptyargumentconst,
         var var06 = gen::g_emptyargumentconst,
         var var07 = gen::g_emptyargumentconst,
         var var08 = gen::g_emptyargumentconst,
         var var09 = gen::g_emptyargumentconst,
         var var10 = gen::g_emptyargumentconst,
         var var11 = gen::g_emptyargumentconst,
         var var12 = gen::g_emptyargumentconst,
         var var13 = gen::g_emptyargumentconst,
         var var14 = gen::g_emptyargumentconst,
         var var15 = gen::g_emptyargumentconst,
         var var16 = gen::g_emptyargumentconst,
         var var17 = gen::g_emptyargumentconst,
         var var18 = gen::g_emptyargumentconst,
         var var19 = gen::g_emptyargumentconst,
         var var20 = gen::g_emptyargumentconst,
         var var21 = gen::g_emptyargumentconst,
         var var22 = gen::g_emptyargumentconst,
         var var23 = gen::g_emptyargumentconst,
         var var24 = gen::g_emptyargumentconst,
         var var25 = gen::g_emptyargumentconst) = 0;

      virtual bool is_array(var var) = 0;

      virtual var array_merge(
         var var01 = gen::g_emptyargumentconst,
         var var02 = gen::g_emptyargumentconst,
         var var03 = gen::g_emptyargumentconst,
         var var04 = gen::g_emptyargumentconst,
         var var05 = gen::g_emptyargumentconst,
         var var06 = gen::g_emptyargumentconst,
         var var07 = gen::g_emptyargumentconst,
         var var08 = gen::g_emptyargumentconst,
         var var09 = gen::g_emptyargumentconst,
         var var10 = gen::g_emptyargumentconst,
         var var11 = gen::g_emptyargumentconst,
         var var12 = gen::g_emptyargumentconst,
         var var13 = gen::g_emptyargumentconst,
         var var14 = gen::g_emptyargumentconst,
         var var15 = gen::g_emptyargumentconst,
         var var16 = gen::g_emptyargumentconst,
         var var17 = gen::g_emptyargumentconst,
         var var18 = gen::g_emptyargumentconst,
         var var19 = gen::g_emptyargumentconst,
         var var20 = gen::g_emptyargumentconst,
         var var21 = gen::g_emptyargumentconst,
         var var22 = gen::g_emptyargumentconst,
         var var23 = gen::g_emptyargumentconst,
         var var24 = gen::g_emptyargumentconst,
         var var25 = gen::g_emptyargumentconst) = 0;

      virtual void echo_simage(var param_view) = 0;
      virtual string simage(var param_view) = 0;
      virtual void simage_add_accepta(webserver::simage_accepta * paccepta) = 0;
      virtual string simage_relative(var param_view) = 0;

      virtual bool net_hostname_is_spider(const char * hostname, const char * useragent = NULL) = 0;
      virtual void add_spider_match_host(const char * hostname, const char * useragent = NULL) = 0;

      virtual script_interface & main() = 0;

      virtual ::http::file & output_file() = 0;

      virtual void filter_user_presence_status(const char * pszUserId) = 0;

      virtual bool is_licensed(const char * pszLicense, const char * pszUserId) = 0;

      virtual void menuleft_printVert001(webserver::ui_menu * pmenu, int iPanelIndex) = 0;

      virtual string web_map(const char * psz) = 0;


      virtual bool is_site_user(var varSite, var varUser) = 0;
      virtual bool is_site_user(var varSite) = 0;

      virtual string    low_fs_file_path        (const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension) = 0;
      virtual bool      low_fs_read             (const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension) = 0;
      virtual __int64   low_fs_map              (const char * pszDir) = 0;
      virtual bool      low_fs_map_file         (const char * pszPath) = 0;
      virtual bool      low_fs_license          (const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension) = 0;
      virtual bool      low_fs_is_licensed      (const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension) = 0;

      virtual bool      low_fs_read             (const char * user, __int64 iFolder, const char * pszName) = 0;
      virtual bool      low_fs_add_user_file    (const char * user, __int64 iFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char *pszName, bool bOverwrite) = 0;
      virtual __int64   low_fs_add_user_dir     (const char * user, __int64 iFolder, const char * pszName) = 0;
      virtual void      low_fs_ls_dir           (const char * user, __int64 iFolder, int64_array & ia, stringa & stra) = 0;
      virtual void      low_fs_ls_file          (const char * user, __int64 iFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName) = 0;


      virtual bool      low_folder(string & strUser, __int64 & iFolder , const char * pszFolder) = 0;

      virtual bool      low_folder_lazy_file(string & strUser, __int64 & iFolder , string & strFile, const char * pszPath);

      virtual bool      mid_fs_read             (const char * pszFolder, const char * pszName);

      virtual bool      fs_read                 (const char * pszPath);
      virtual bool      fs_add_user_file        (const char * pszFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char * pszName, bool bOverwrite);
      virtual __int64   fs_add_user_dir         (const char * pszFolder, const char * pszName);
      virtual void      fs_ls_dir               (const char * pszFolder, int64_array & ia, stringa & stra);
      virtual void      fs_ls_file              (const char * pszFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName);

      virtual bool      fs_dir_mk               (const char * pszFolder) = 0;


      virtual string datetime_get_month_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL) = 0;
      virtual string datetime_get_month_short_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL) = 0;
      virtual string datetime_get_weekday_short_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL) = 0;
      virtual string datetime_get_weekday_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL) = 0;

      virtual int datetime_get_month_day_count(int year, int month) = 0;
      // 0 is Sunday
      virtual string datetime_get_weekday(int year, int month, int day) = 0;
      virtual class time datetime_get_timestamp(int year, int  month,  int day) = 0;
      virtual string datetime_getGMTDateTime() = 0;
      virtual string datetime_formatDateTime(class time t) = 0;
      virtual class time datetime_getTimestamp() = 0;
      virtual __int64 datetime_InternationalToUnixMillis(const char * date) = 0;
      virtual string datetime_getToday() = 0;
      virtual class time datetime_strtotime(const char * psz) = 0;
      virtual class time datetime_strtotime(const char * psz, class time t) = 0;

   };


} // namespace dynamic_source