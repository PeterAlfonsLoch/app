#include "StdAfx.h"


namespace dynamic_source
{


   script_composite::script_composite()
   {
      ::sockets::socket::SocketThread * pthread = dynamic_cast < ::sockets::socket::SocketThread * > (::ca::get_thread());
      if(pthread != NULL)
      {
         netnode::socket * psocket = dynamic_cast < netnode::socket * > (pthread->GetSocket());
         m_pinterface = psocket->m_pinstanceCurrent;
         set_app(m_pinterface->get_app());
      }
      else
      {
         m_pinterface = NULL;
      }
   }

   script_composite::~script_composite()
   {
   }


   void script_composite::script_start()
   {
      m_pinterface->script_start();
   }

   void script_composite::script_step()
   {
      m_pinterface->script_step();
   }

   void script_composite::script_end()
   {
      m_pinterface->script_end();
   }



   void script_composite::get_output(string & strHeader, http::memory_file & memfile)
   {
      m_pinterface->get_output(strHeader, memfile);
   }


   gen::property & script_composite::gprop(const char * pszKey)
   {
      return m_pinterface->gprop(pszKey);
   }









   void script_composite::ds_print(const char * lpcsz)
   {
      m_pinterface->ds_print(lpcsz);
   }

   void script_composite::raw_print(const char * lpcsz)
   {
      m_pinterface->raw_print(lpcsz);
   }

   void script_composite::print_r(var var)
   {
      m_pinterface->print_r(var);
   }

   void script_composite::print(const char * lpcsz)
   {
      m_pinterface->print(lpcsz);
   }

   bool script_composite::read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea, const char * pszContentType)
   {
      return m_pinterface->read_file(lpcsz, prangea, pszContentType);
   }




   var script_composite::include(const char * lpcsz)
   {
      return m_pinterface->include(lpcsz);
   }

   void script_composite::launch(const char * lpcsz)
   {
      m_pinterface->launch(lpcsz);
   }




   void script_composite::edgify(int iEdge, ::userbase::document_template * ptemplate, bool bMakeVisible)
   {
      m_pinterface->edgify(iEdge, ptemplate, bMakeVisible);
   }

   void script_composite::edgify_app(int iEdge, ::ca::type_info prtcApp, bool bMakeVisible)
   {
      m_pinterface->edgify_app(iEdge, prtcApp, bMakeVisible);
   }

   void script_composite::hand_root()
   {
      m_pinterface->hand_root();
   }

   void script_composite::hand_karaoke()
   {
      m_pinterface->hand_karaoke();
   }

   void script_composite::hand_cifras()
   {
      m_pinterface->hand_cifras();
   }

   void script_composite::hand_letras()
   {
      m_pinterface->hand_letras();
   }

   string script_composite::ui_exuri()
   {
      return m_pinterface->ui_exuri();
   }


   void script_composite::ui_nav_printOut5(stringa & straLink, stringa & straTitle)
   {
      m_pinterface->ui_nav_printOut5(straLink, straTitle);
   }

   void script_composite::ui_nav_printOut3(stringa & straLink, stringa & straTitle)
   {
      m_pinterface->ui_nav_printOut3(straLink, straTitle);
   }


   void script_composite::ui_nav_printOut2(stringa & straLink, stringa & straTitle)
   {
      m_pinterface->ui_nav_printOut2(straLink, straTitle);
   }


   void script_composite::ui_nav_printOut1(stringa & straLink, stringa & straTitle)
   {
      m_pinterface->ui_nav_printOut1(straLink, straTitle);
   }

   bool script_composite::script_right()
   {
      return m_pinterface->script_right();
   }

   void script_composite::dprint_r(var var)
   {
      m_pinterface->dprint_r(var);
   }

   void script_composite::dprint(const char * psz)
   {
      m_pinterface->dprint(psz);
   }

   void script_composite::dinit()
   {
      m_pinterface->dinit();
   }

   void script_composite::dfinish()
   {
      m_pinterface->dfinish();
   }

   __int64 script_composite::get_first_time()
   {
      return m_pinterface->get_first_time();
   }

   void script_composite::prof_enter(const char * psz)
   {
      m_pinterface->prof_enter(psz);
   }

   void script_composite::prof_leave(const char * psz)
   {
      m_pinterface->prof_leave(psz);
   }

   void script_composite::until_here()
   {
      m_pinterface->until_here();
   }

   class profiler * script_composite::profiler()
   {
      return m_pinterface->profiler();
   }

   string script_composite::real_path(const char * psz)
   {
      return m_pinterface->real_path(psz);
   }

   string script_composite::system_path(const char * psz)
   {
      return m_pinterface->system_path(psz);
   }

   string script_composite::pstr(const char * pszTopic, const char * pszLocale, const char * pszStyle)
   {
      return m_pinterface->pstr(pszTopic, pszLocale, pszStyle);
   }

   string script_composite::pstr(const char * pszTopic, gen::property_set & set, const char * pszLocale, const char * pszStyle)
   {
      return m_pinterface->pstr(pszTopic, set, pszLocale, pszStyle);
   }

   string script_composite::langstr(const char * pszKey)
   {
      return m_pinterface->langstr(pszKey);
   }

   string script_composite::langstr2(const char * pszKey)
   {
      return m_pinterface->langstr2(pszKey);
   }

   void script_composite::print_langstr(const char * pszKey)
   {
      m_pinterface->print_langstr(pszKey);
   }

   void script_composite::set_langstr(const char * pszKey, const char * pszValue)
   {
      m_pinterface->set_langstr(pszKey, pszValue);
   }

   string script_composite::current_url()
   {
      return m_pinterface->current_url();
   }

   string script_composite::urlencode(const char * psz)
   {
      return m_pinterface->urlencode(psz);
   }

   string script_composite::urldecode(const char * psz)
   {
      return m_pinterface->urldecode(psz);
   }

   string script_composite::htmlspecialchars(const char * psz)
   {
      return m_pinterface->htmlspecialchars(psz);
   }

   string script_composite::htmlentities(const char * psz)
   {
      return m_pinterface->htmlentities(psz);
   }


   void script_composite::run()
   {
      m_pinterface->run();
   }

   string script_composite::ui_redir(const char * pszLang, const char * pszStyle, const char * pszExUri, const char * pszRoot)
   {
      return m_pinterface->ui_redir(pszLang, pszStyle, pszExUri, pszRoot);
   }

   void script_composite::ui_redir_add(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszTarget)
   {
      return m_pinterface->ui_redir_add(pszRoot, pszLang, pszStyle, pszTarget);
   }

   string script_composite::sys_get_include_path(const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept)
   {
      return m_pinterface->sys_get_include_path(pszExt, pszType, pszDoc, pstraAccept);
   }
   string script_composite::named_sys_get_include_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept)
   {
      return m_pinterface->named_sys_get_include_path(pszSystemPath, pszExt, pszType, pszDoc, pstraAccept);
   }
   string script_composite::sys_get_base_path(const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept)
   {
      return m_pinterface->sys_get_base_path(pszExt, pszType, pszDoc, pszBase, pstraAccept);
   }
   string script_composite::named_sys_get_base_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept)
   {
      return m_pinterface->named_sys_get_base_path(pszSystemPath, pszExt, pszType, pszDoc, pszBase, pstraAccept);
   }
   string script_composite::sys_get_subdomain_path(const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept)
   {
      return m_pinterface->sys_get_subdomain_path(pszExt, pszType, pszDoc, pszBase, pszSubdomain, pstraAccept);
   }
   string script_composite::named_sys_get_subdomain_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept)
   {
      return m_pinterface->named_sys_get_subdomain_path(pszSystemPath, pszExt, pszType, pszDoc, pszBase, pszSubdomain, pstraAccept);
   }


   ::webserver::fun::fun & script_composite::fun()
   {
      return m_pinterface->fun();
   }

   ::webserver::fontopus_database & script_composite::musicdb()
   {
      return m_pinterface->musicdb();
   }

   ::webserver::fontopus_database & script_composite::musicdb_se()
   {
      return m_pinterface->musicdb_se();
   }

   ::webserver::fontopus_database & script_composite::admindb()
   {
      return m_pinterface->admindb();
   }

   ::webserver::secure & script_composite::secure()
   {
      return m_pinterface->secure();
   }

   ::webserver::music::music & script_composite::music()
   {
      return m_pinterface->music();
   }

   ::webserver::cynce_database & script_composite::cyncedb()
   {
      return m_pinterface->cyncedb();
   }

   ::webserver::cynce & script_composite::cynce()
   {
      return m_pinterface->cynce();
   }

   ::webserver::user & script_composite::user()
   {
      return m_pinterface->user();
   }

   ::webserver::wb & script_composite::wb()
   {
      return m_pinterface->wb();
   }

   void script_composite::keep(ptr * pptr)
   {
      m_pinterface->keep(pptr);
   }

   void script_composite::unkeep(ptr * pptr)
   {
      m_pinterface->unkeep(pptr);
   }


   gen::property & script_composite::get(const char * pszKey)
   {
      return m_pinterface->get(pszKey);
   }
   gen::property & script_composite::post(const char * pszKey)
   {
      return m_pinterface->post(pszKey);
   }
   http::cookie & script_composite::cookie(const char * pszKey)
   {
      return m_pinterface->cookie(pszKey);
   }
   gen::property & script_composite::request(const char * pszKey)
   {
      return m_pinterface->request(pszKey);
   }
   gen::property & script_composite::session(const char * pszKey)
   {
      return m_pinterface->session(pszKey);
   }
   gen::relation_set & script_composite::geta()
   {
      return m_pinterface->geta();
   }
   gen::relation_set & script_composite::posta()
   {
      return m_pinterface->posta();
   }
   http::cookies & script_composite::cookies()
   {
      return m_pinterface->cookies();
   }
   gen::relation_set & script_composite::requesta()
   {
      return m_pinterface->requesta();
   }
   gen::property_set & script_composite::sessiona()
   {
      return m_pinterface->sessiona();
   }

   gen::property_set & script_composite::inattra()
   {
      return m_pinterface->inattra();
   }

   string script_composite::this_url()
   {
      return m_pinterface->this_url();
   }

   string script_composite::session_id(const char * pszId)
   {
      return m_pinterface->session_id(pszId);
   }

   gen::property & script_composite::inheader(const char * psz)
   {
      return m_pinterface->inheader(psz);
   }
   gen::property & script_composite::outheader(const char * psz)
   {
      return m_pinterface->outheader(psz);
   }


   gen::property & script_composite::inattr(const char * psz)
   {
      return m_pinterface->inattr(psz);
   }
   gen::property & script_composite::outattr(const char * psz)
   {
      return m_pinterface->outattr(psz);
   }



   string script_composite::set_cookie(
      const char * pszKey,
      var varValue,
      int iExpire,
      const char * pszPath, 
      const char * pszDomain,
      bool bSecure)
   {
      return m_pinterface->set_cookie(
         pszKey,
         varValue,
         iExpire,
         pszPath,
         pszDomain,
         bSecure);
   }

   string script_composite::uri_set_var(const char * pszQuery, const char * pszKey, var var)
   {
      return m_pinterface->uri_set_var(pszQuery, pszKey, var);
   }

   string script_composite::eval(const char * pszText)
   {
      return m_pinterface->eval(pszText);
   }

   string script_composite::get_current_url()
   {
      return m_pinterface->get_current_url();
   }

   int script_composite::ca2_fetch_mode(int iMode)
   {
      return m_pinterface->ca2_fetch_mode(iMode);
   }

   time_t script_composite::strtotime(const char * psz, time_t time)
   {
      return m_pinterface->strtotime(psz, time);
   }

   time_t script_composite::strtotime(const char * psz)
   {
      return m_pinterface->strtotime(psz);
   }

   string script_composite::strftime(const char * psz, time_t time)
   {
      return m_pinterface->strftime(psz, time);
   }

   string script_composite::strftime(const char * psz)
   {
      return m_pinterface->strftime(psz);
   }

   var script_composite::rand(var start, var end)
   {
      return m_pinterface->rand(start, end);
   }


   int script_composite::exit(int iExitCode)
   {
      return m_pinterface->exit(iExitCode);
   }

   script_manager * script_composite::get_manager()
   {
      return m_pinterface->get_manager();
   }

   netnode::socket & script_composite::netnode()
   {
      return m_pinterface->netnode();
   }

   void script_composite::header(const char * pszHeader)
   {
      m_pinterface->header(pszHeader);
   }

   string script_composite::ui_url(const char * pszTopic, const char * pszStyle)
   {
      return m_pinterface->ui_url(pszTopic, pszStyle);
   }

   void script_composite::cla_sel1(const char * section, const char * item)
   {
      return m_pinterface->cla_sel1(section, item);
   }


   string script_composite::datetime_get_month_str(int idx, const char * pszLocale, const char * pszStyle)
   {
      return m_pinterface->datetime_get_month_str(idx, pszLocale, pszStyle);
   }

   string script_composite::datetime_get_month_short_str(int idx, const char * pszLocale, const char * pszStyle)
   {
      return m_pinterface->datetime_get_month_short_str(idx, pszLocale, pszStyle);
   }

   string script_composite::datetime_get_weekday_short_str(int idx, const char * pszLocale, const char * pszStyle)
   {
      return m_pinterface->datetime_get_weekday_short_str(idx, pszLocale, pszStyle);
   }

   string script_composite::datetime_get_weekday_str(int idx, const char * pszLocale, const char * pszStyle)
   {
      return m_pinterface->datetime_get_weekday_str(idx, pszLocale, pszStyle);
   }

   string script_composite::spa_calc_best_host()
   {
      return m_pinterface->spa_calc_best_host();
   }

   GeoIPRecord * script_composite::get_client_geopip_record()
   {
      return m_pinterface->get_client_geopip_record();
   }

   void script_composite::image_png(::ca::bitmap_sp pbitmap)
   {
      m_pinterface->image_png(pbitmap);
   }

   var script_composite::explode(const char * pszDelimiter, const char * psz)
   {
      return m_pinterface->explode(pszDelimiter, psz);
   }

   string script_composite::implode(const char * pszDelimiter, const var & var)
   {
      return m_pinterface->implode(pszDelimiter, var);
   }

   bool script_composite::in_array(const var & varElement, const var & varArray)
   {
      return m_pinterface->in_array(varElement, varArray);
   }

   void script_composite::array_unshift(var & varArray, const var varElement)
   {
      m_pinterface->array_unshift(varArray, varElement);
   }

   int script_composite::count(var var)
   {
      return m_pinterface->count(var);
   }

   var script_composite::array(
      var var01,
      var var02,
      var var03,
      var var04,
      var var05,
      var var06,
      var var07,
      var var08,
      var var09,
      var var10,
      var var11,
      var var12,
      var var13,
      var var14,
      var var15,
      var var16,
      var var17,
      var var18,
      var var19,
      var var20,
      var var21,
      var var22,
      var var23,
      var var24,
      var var25)
   {
      return m_pinterface->array(
         var01,
         var02,
         var03,
         var04,
         var05,
         var06,
         var07,
         var08,
         var09,
         var10,
         var11,
         var12,
         var13,
         var14,
         var15,
         var16,
         var17,
         var18,
         var19,
         var20,
         var21,
         var22,
         var23,
         var24,
         var25);
   }


   bool script_composite::is_array(var var)
   {
      return m_pinterface->is_array(var);
   }


   var script_composite::array_merge(
      var var01,
      var var02,
      var var03,
      var var04,
      var var05,
      var var06,
      var var07,
      var var08,
      var var09,
      var var10,
      var var11,
      var var12,
      var var13,
      var var14,
      var var15,
      var var16,
      var var17,
      var var18,
      var var19,
      var var20,
      var var21,
      var var22,
      var var23,
      var var24,
      var var25)
   {
      return m_pinterface->array_merge(
         var01,
         var02,
         var03,
         var04,
         var05,
         var06,
         var07,
         var08,
         var09,
         var10,
         var11,
         var12,
         var13,
         var14,
         var15,
         var16,
         var17,
         var18,
         var19,
         var20,
         var21,
         var22,
         var23,
         var24,
         var25);
   }

   void script_composite::echo_simage(var param_view)
   {
      m_pinterface->echo_simage(param_view);
   }

   string script_composite::simage(var param_view)
   {
      return m_pinterface->simage(param_view);
   }

   void script_composite::simage_add_accepta(webserver::simage_accepta * paccepta)
   {
      m_pinterface->simage_add_accepta(paccepta);
   }

   string script_composite::simage_relative(var param_view)
   {
      return m_pinterface->simage_relative(param_view);
   }

   bool script_composite::net_hostname_is_spider(const char * hostname, const char * useragent)
   {
      return m_pinterface->net_hostname_is_spider(hostname, useragent);
   }

   void script_composite::add_spider_match_host(const char * hostname, const char * useragent)
   {
      return m_pinterface->add_spider_match_host(hostname, useragent);
   }


   script_interface & script_composite::main()
   {
      return m_pinterface->main();
   }

   ::user::str_context * script_composite::str_context()
   {
      return m_pinterface->str_context();
   }

   ::http::file & script_composite::output_file()
   {
      return m_pinterface->output_file();
   }

   void script_composite::filter_user_presence_status(const char * pszUserId)
   {
      m_pinterface->filter_user_presence_status(pszUserId);
   }

   bool script_composite::is_licensed(const char * pszLicense, const char * pszUserId)
   {
      return m_pinterface->is_licensed(pszLicense, pszUserId);
   }

   void script_composite::menuleft_printVert001(webserver::ui_menu * pmenu, int iPanelIndex)
   {
      return m_pinterface->menuleft_printVert001(pmenu, iPanelIndex);
   }

   string script_composite::web_map(const char * psz)
   {
      return m_pinterface->web_map(psz);
   }

   bool script_composite::is_site_user(var varSite, var varUser)
   {
      return m_pinterface->is_site_user(varSite, varUser);
   }

   bool script_composite::is_site_user(var varSite)
   {
      return m_pinterface->is_site_user(varSite);
   }

   string script_composite::low_fs_file_path(const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, gen::property_set set)
   {
      return m_pinterface->low_fs_file_path(hash, key, size, mimetype, extension, set);
   }

   bool script_composite::low_fs_read(const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension)
   {
      return m_pinterface->low_fs_read(hash, key, size, mimetype, extension);
   }

   bool script_composite::low_fs_read(const char * user, __int64 iFolder, const char * pszName)
   {
      return m_pinterface->low_fs_read(user, iFolder, pszName);
   }


   __int64 script_composite::low_fs_map(const char * pszDir)
   {
      return m_pinterface->low_fs_map(pszDir);
   }

   bool script_composite::low_fs_map_file(const char * pszPath)
   {
      return m_pinterface->low_fs_map_file(pszPath);
   }

   bool script_composite::low_fs_license(const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension)
   {
      return m_pinterface->low_fs_license(user, hash, key, size, mimetype, extension);
   }

   bool script_composite::low_fs_is_licensed(const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension)
   {
      return m_pinterface->low_fs_is_licensed(user, hash, key, size, mimetype, extension);
   }

   bool script_composite::low_fs_add_user_file(const char * user, __int64 iFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char * pszName, bool bOverwrite)
   {
      return m_pinterface->low_fs_add_user_file(user, iFolder, hash, key, size, mimetype, extension, pszName, bOverwrite);
   }

   __int64 script_composite::low_fs_add_user_dir(const char * user, __int64 iParentFolder, const char * pszName)
   {
      return m_pinterface->low_fs_add_user_dir(user, iParentFolder, pszName);
   }

   void script_composite::low_fs_ls_dir(const char * user, __int64 iParentFolder, int64_array & ia, stringa & stra)
   {
      return m_pinterface->low_fs_ls_dir(user, iParentFolder, ia, stra);
   }

   void script_composite::low_fs_ls_file(const char * user, __int64 iFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName)
   {
      return m_pinterface->low_fs_ls_file(user, iFolder, straHash, iaKey, iaSize, straMime, straExt, straName);
   }

   bool script_composite::low_folder(string & strUser, __int64 & iFolder, const char * pszFolder)
   {
      return m_pinterface->low_folder(strUser, iFolder, pszFolder);
   }

   bool script_composite::fs_dir_mk(const char * pszFolder)
   {
      return m_pinterface->fs_dir_mk(pszFolder);
   }

   int script_composite::datetime_get_month_day_count(int year, int month)
   {
      return m_pinterface->datetime_get_month_day_count(year, month);
   }

   // 0 is Sunday
   string script_composite::datetime_get_weekday(int year, int month, int day)
   {
      return m_pinterface->datetime_get_weekday(year, month, day);
   }

   class time script_composite::datetime_get_timestamp(int year, int  month,  int day)
   {
      return m_pinterface->datetime_get_timestamp(year, month, day);
   }

   string script_composite::datetime_getGMTDateTime()
   {
      return m_pinterface->datetime_getGMTDateTime();
   }

   string script_composite::datetime_formatDateTime(class time t)
   {
      return m_pinterface->datetime_formatDateTime(t);
   }

   class time script_composite::datetime_getTimestamp()
   {
      return m_pinterface->datetime_getTimestamp();
   }

   __int64 script_composite::datetime_InternationalToUnixMillis(const char * date)
   {
      return m_pinterface->datetime_InternationalToUnixMillis(date);
   }

   string script_composite::datetime_getToday()
   {
      return m_pinterface->datetime_getToday();
   }

   class time script_composite::datetime_strtotime(const char * psz)
   {
      return m_pinterface->datetime_strtotime(psz);
   }

   class time script_composite::datetime_strtotime(const char * psz, class time t)
   {
      return m_pinterface->datetime_strtotime(psz, t);
   }

} // namespace dynamic_source