#include "StdAfx.h"

netnodeScriptComposite::netnodeScriptComposite()
{
   ::sockets::socket::SocketThread * pthread = dynamic_cast < ::sockets::socket::SocketThread * > (::ca::get_thread());
   if(pthread != NULL)
   {
      netnodeSocket * psocket = dynamic_cast < netnodeSocket * > (pthread->GetSocket());
      m_pinterface = psocket->m_pinstanceCurrent;
      set_app(m_pinterface->get_app());
   }
   else
   {
      m_pinterface = NULL;
   }
}

netnodeScriptComposite::~netnodeScriptComposite()
{
}


void netnodeScriptComposite::script_start()
{
   m_pinterface->script_start();
}

void netnodeScriptComposite::script_step()
{
   m_pinterface->script_step();
}

void netnodeScriptComposite::script_end()
{
   m_pinterface->script_end();
}



void netnodeScriptComposite::get_output(string & strHeader, http::memory_file & memfile)
{
   m_pinterface->get_output(strHeader, memfile);
}


gen::property & netnodeScriptComposite::gprop(const char * pszKey)
{
   return m_pinterface->gprop(pszKey);
}









void netnodeScriptComposite::ds_print(const char * lpcsz)
{
   m_pinterface->ds_print(lpcsz);
}

void netnodeScriptComposite::raw_print(const char * lpcsz)
{
   m_pinterface->raw_print(lpcsz);
}

void netnodeScriptComposite::print_r(var var)
{
   m_pinterface->print_r(var);
}

void netnodeScriptComposite::print(const char * lpcsz)
{
   m_pinterface->print(lpcsz);
}

bool netnodeScriptComposite::read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea)
{
   return m_pinterface->read_file(lpcsz, prangea);
}




var netnodeScriptComposite::include(const char * lpcsz)
{
   return m_pinterface->include(lpcsz);
}

void netnodeScriptComposite::launch(const char * lpcsz)
{
   m_pinterface->launch(lpcsz);
}




void netnodeScriptComposite::edgify(int iEdge, ::userbase::document_template * ptemplate, bool bMakeVisible)
{
   m_pinterface->edgify(iEdge, ptemplate, bMakeVisible);
}

void netnodeScriptComposite::edgify_app(int iEdge, ::ca::type_info prtcApp, bool bMakeVisible)
{
   m_pinterface->edgify_app(iEdge, prtcApp, bMakeVisible);
}

void netnodeScriptComposite::hand_root()
{
   m_pinterface->hand_root();
}

void netnodeScriptComposite::hand_karaoke()
{
   m_pinterface->hand_karaoke();
}

void netnodeScriptComposite::hand_cifras()
{
   m_pinterface->hand_cifras();
}

void netnodeScriptComposite::hand_letras()
{
   m_pinterface->hand_letras();
}

string netnodeScriptComposite::ui_exuri()
{
   return m_pinterface->ui_exuri();
}


void netnodeScriptComposite::ui_nav_printOut5(stringa & straLink, stringa & straTitle)
{
   m_pinterface->ui_nav_printOut5(straLink, straTitle);
}

void netnodeScriptComposite::ui_nav_printOut3(stringa & straLink, stringa & straTitle)
{
   m_pinterface->ui_nav_printOut3(straLink, straTitle);
}


void netnodeScriptComposite::ui_nav_printOut2(stringa & straLink, stringa & straTitle)
{
   m_pinterface->ui_nav_printOut2(straLink, straTitle);
}


void netnodeScriptComposite::ui_nav_printOut1(stringa & straLink, stringa & straTitle)
{
   m_pinterface->ui_nav_printOut1(straLink, straTitle);
}

bool netnodeScriptComposite::script_right()
{
   return m_pinterface->script_right();
}

void netnodeScriptComposite::dprint_r(var var)
{
   m_pinterface->dprint_r(var);
}

void netnodeScriptComposite::dprint(const char * psz)
{
   m_pinterface->dprint(psz);
}

void netnodeScriptComposite::dinit()
{
   m_pinterface->dinit();
}

void netnodeScriptComposite::dfinish()
{
   m_pinterface->dfinish();
}

__int64 netnodeScriptComposite::get_first_time()
{
   return m_pinterface->get_first_time();
}

void netnodeScriptComposite::prof_enter(const char * psz)
{
   m_pinterface->prof_enter(psz);
}

void netnodeScriptComposite::prof_leave(const char * psz)
{
   m_pinterface->prof_leave(psz);
}

void netnodeScriptComposite::until_here()
{
   m_pinterface->until_here();
}

class netnode::profiler * netnodeScriptComposite::profiler()
{
   return m_pinterface->profiler();
}

string netnodeScriptComposite::real_path(const char * psz)
{
   return m_pinterface->real_path(psz);
}

string netnodeScriptComposite::system_path(const char * psz)
{
   return m_pinterface->system_path(psz);
}

string netnodeScriptComposite::pstr(const char * pszTopic, const char * pszLocale, const char * pszStyle)
{
   return m_pinterface->pstr(pszTopic, pszLocale, pszStyle);
}

string netnodeScriptComposite::pstr(const char * pszTopic, gen::property_set & set, const char * pszLocale, const char * pszStyle)
{
   return m_pinterface->pstr(pszTopic, set, pszLocale, pszStyle);
}

string netnodeScriptComposite::langstr(const char * pszKey)
{
   return m_pinterface->langstr(pszKey);
}

string netnodeScriptComposite::langstr2(const char * pszKey)
{
   return m_pinterface->langstr2(pszKey);
}

void netnodeScriptComposite::print_langstr(const char * pszKey)
{
   m_pinterface->print_langstr(pszKey);
}

void netnodeScriptComposite::set_langstr(const char * pszKey, const char * pszValue)
{
   m_pinterface->set_langstr(pszKey, pszValue);
}

string netnodeScriptComposite::current_url()
{
   return m_pinterface->current_url();
}

string netnodeScriptComposite::urlencode(const char * psz)
{
   return m_pinterface->urlencode(psz);
}

string netnodeScriptComposite::urldecode(const char * psz)
{
   return m_pinterface->urldecode(psz);
}

string netnodeScriptComposite::htmlspecialchars(const char * psz)
{
   return m_pinterface->htmlspecialchars(psz);
}

string netnodeScriptComposite::htmlentities(const char * psz)
{
   return m_pinterface->htmlentities(psz);
}


void netnodeScriptComposite::run()
{
   m_pinterface->run();
}

string netnodeScriptComposite::ui_redir(const char * pszLang, const char * pszStyle, const char * pszExUri, const char * pszRoot)
{
   return m_pinterface->ui_redir(pszLang, pszStyle, pszExUri, pszRoot);
}

void netnodeScriptComposite::ui_redir_add(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszTarget)
{
   return m_pinterface->ui_redir_add(pszRoot, pszLang, pszStyle, pszTarget);
}

string netnodeScriptComposite::sys_get_include_path(const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept)
{
   return m_pinterface->sys_get_include_path(pszExt, pszType, pszDoc, pstraAccept);
}
string netnodeScriptComposite::named_sys_get_include_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept)
{
   return m_pinterface->sys_get_include_path(pszExt, pszType, pszDoc, pstraAccept);
}
string netnodeScriptComposite::sys_get_base_path(const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept)
{
   return m_pinterface->sys_get_base_path(pszExt, pszType, pszDoc, pszBase, pstraAccept);
}
string netnodeScriptComposite::named_sys_get_base_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept)
{
   return m_pinterface->named_sys_get_base_path(pszSystemPath, pszExt, pszType, pszDoc, pszBase, pstraAccept);
}
string netnodeScriptComposite::sys_get_subdomain_path(const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept)
{
   return m_pinterface->sys_get_subdomain_path(pszExt, pszType, pszDoc, pszBase, pszSubdomain, pstraAccept);
}
string netnodeScriptComposite::named_sys_get_subdomain_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept)
{
   return m_pinterface->named_sys_get_subdomain_path(pszSystemPath, pszExt, pszType, pszDoc, pszBase, pszSubdomain, pstraAccept);
}


fun & netnodeScriptComposite::fun()
{
   return m_pinterface->fun();
}

fontopus_database & netnodeScriptComposite::musicdb()
{
   return m_pinterface->musicdb();
}

fontopus_database & netnodeScriptComposite::musicdb_se()
{
   return m_pinterface->musicdb_se();
}

fontopus_database & netnodeScriptComposite::admindb()
{
   return m_pinterface->admindb();
}

secure & netnodeScriptComposite::secure()
{
   return m_pinterface->secure();
}

netnode::music & netnodeScriptComposite::music()
{
   return m_pinterface->music();
}

cynce_database & netnodeScriptComposite::cyncedb()
{
   return m_pinterface->cyncedb();
}

cynce & netnodeScriptComposite::cynce()
{
   return m_pinterface->cynce();
}

netnode::user & netnodeScriptComposite::user()
{
   return m_pinterface->user();
}

netnode::wb & netnodeScriptComposite::wb()
{
   return m_pinterface->wb();
}

void netnodeScriptComposite::keep(ptr * pptr)
{
   m_pinterface->keep(pptr);
}

void netnodeScriptComposite::unkeep(ptr * pptr)
{
   m_pinterface->unkeep(pptr);
}


gen::property & netnodeScriptComposite::get(const char * pszKey)
{
   return m_pinterface->get(pszKey);
}
gen::property & netnodeScriptComposite::post(const char * pszKey)
{
   return m_pinterface->post(pszKey);
}
http::cookie & netnodeScriptComposite::cookie(const char * pszKey)
{
   return m_pinterface->cookie(pszKey);
}
gen::property & netnodeScriptComposite::request(const char * pszKey)
{
   return m_pinterface->request(pszKey);
}
gen::property & netnodeScriptComposite::session(const char * pszKey)
{
   return m_pinterface->session(pszKey);
}
gen::relation_set & netnodeScriptComposite::geta()
{
   return m_pinterface->geta();
}
gen::relation_set & netnodeScriptComposite::posta()
{
   return m_pinterface->posta();
}
http::cookies & netnodeScriptComposite::cookies()
{
   return m_pinterface->cookies();
}
gen::relation_set & netnodeScriptComposite::requesta()
{
   return m_pinterface->requesta();
}
gen::property_set & netnodeScriptComposite::sessiona()
{
   return m_pinterface->sessiona();
}

gen::property_set & netnodeScriptComposite::inattra()
{
   return m_pinterface->inattra();
}

string netnodeScriptComposite::this_url()
{
   return m_pinterface->this_url();
}

string netnodeScriptComposite::session_id(const char * pszId)
{
   return m_pinterface->session_id(pszId);
}

gen::property & netnodeScriptComposite::inheader(const char * psz)
{
   return m_pinterface->inheader(psz);
}
gen::property & netnodeScriptComposite::outheader(const char * psz)
{
   return m_pinterface->outheader(psz);
}


gen::property & netnodeScriptComposite::inattr(const char * psz)
{
   return m_pinterface->inattr(psz);
}
gen::property & netnodeScriptComposite::outattr(const char * psz)
{
   return m_pinterface->outattr(psz);
}



string netnodeScriptComposite::set_cookie(
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

string netnodeScriptComposite::uri_set_var(const char * pszQuery, const char * pszKey, var var)
{
   return m_pinterface->uri_set_var(pszQuery, pszKey, var);
}

string netnodeScriptComposite::eval(const char * pszText)
{
   return m_pinterface->eval(pszText);
}

string netnodeScriptComposite::get_current_url()
{
   return m_pinterface->get_current_url();
}

int netnodeScriptComposite::ca2_fetch_mode(int iMode)
{
   return m_pinterface->ca2_fetch_mode(iMode);
}

time_t netnodeScriptComposite::strtotime(const char * psz, time_t time)
{
   return m_pinterface->strtotime(psz, time);
}

time_t netnodeScriptComposite::strtotime(const char * psz)
{
   return m_pinterface->strtotime(psz);
}

string netnodeScriptComposite::strftime(const char * psz, time_t time)
{
   return m_pinterface->strftime(psz, time);
}

string netnodeScriptComposite::strftime(const char * psz)
{
   return m_pinterface->strftime(psz);
}

var netnodeScriptComposite::rand(var start, var end)
{
   return m_pinterface->rand(start, end);
}


int netnodeScriptComposite::exit(int iExitCode)
{
   return m_pinterface->exit(iExitCode);
}

netnodeScriptManager * netnodeScriptComposite::get_manager()
{
   return m_pinterface->get_manager();
}

netnodeSocket & netnodeScriptComposite::netnode()
{
   return m_pinterface->netnode();
}

void netnodeScriptComposite::header(const char * pszHeader)
{
   m_pinterface->header(pszHeader);
}

string netnodeScriptComposite::ui_url(const char * pszTopic, const char * pszStyle)
{
   return m_pinterface->ui_url(pszTopic, pszStyle);
}

string netnodeScriptComposite::datetime_get_month_str(int idx, const char * pszLocale, const char * pszStyle)
{
   return m_pinterface->datetime_get_month_str(idx, pszLocale, pszStyle);
}

string netnodeScriptComposite::datetime_get_month_short_str(int idx, const char * pszLocale, const char * pszStyle)
{
   return m_pinterface->datetime_get_month_short_str(idx, pszLocale, pszStyle);
}

string netnodeScriptComposite::datetime_get_weekday_short_str(int idx, const char * pszLocale, const char * pszStyle)
{
   return m_pinterface->datetime_get_weekday_short_str(idx, pszLocale, pszStyle);
}

string netnodeScriptComposite::datetime_get_weekday_str(int idx, const char * pszLocale, const char * pszStyle)
{
   return m_pinterface->datetime_get_weekday_str(idx, pszLocale, pszStyle);
}

string netnodeScriptComposite::spa_calc_best_host()
{
   return m_pinterface->spa_calc_best_host();
}

GeoIPRecord * netnodeScriptComposite::get_client_geopip_record()
{
   return m_pinterface->get_client_geopip_record();
}

void netnodeScriptComposite::image_png(::ca::bitmap_sp pbitmap)
{
   m_pinterface->image_png(pbitmap);
}

var netnodeScriptComposite::explode(const char * pszDelimiter, const char * psz)
{
   return m_pinterface->explode(pszDelimiter, psz);
}

string netnodeScriptComposite::implode(const char * pszDelimiter, const var & var)
{
   return m_pinterface->implode(pszDelimiter, var);
}

bool netnodeScriptComposite::in_array(const var & varElement, const var & varArray)
{
   return m_pinterface->in_array(varElement, varArray);
}

void netnodeScriptComposite::array_unshift(var & varArray, const var varElement)
{
   m_pinterface->array_unshift(varArray, varElement);
}

int netnodeScriptComposite::count(var var)
{
   return m_pinterface->count(var);
}

var netnodeScriptComposite::array(
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


bool netnodeScriptComposite::is_array(var var)
{
   return m_pinterface->is_array(var);
}


var netnodeScriptComposite::array_merge(
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

void netnodeScriptComposite::echo_simage(var param_view)
{
   m_pinterface->echo_simage(param_view);
}

string netnodeScriptComposite::simage(var param_view)
{
   return m_pinterface->simage(param_view);
}

void netnodeScriptComposite::simage_add_accepta(netnode::simage_accepta * paccepta)
{
   m_pinterface->simage_add_accepta(paccepta);
}

string netnodeScriptComposite::simage_relative(var param_view)
{
   return m_pinterface->simage_relative(param_view);
}

bool netnodeScriptComposite::net_hostname_is_spider(const char * hostname, const char * useragent)
{
   return m_pinterface->net_hostname_is_spider(hostname, useragent);
}

void netnodeScriptComposite::add_spider_match_host(const char * hostname, const char * useragent)
{
   return m_pinterface->add_spider_match_host(hostname, useragent);
}


netnodeScriptInterface & netnodeScriptComposite::main()
{
   return m_pinterface->main();
}

::user::str_context * netnodeScriptComposite::str_context()
{
   return m_pinterface->str_context();
}

::http::file & netnodeScriptComposite::output_file()
{
   return m_pinterface->output_file();
}

void netnodeScriptComposite::filter_user_presence_status(const char * pszUserId)
{
   m_pinterface->filter_user_presence_status(pszUserId);
}

bool netnodeScriptComposite::is_licensed(const char * pszLicense, const char * pszUserId)
{
   return m_pinterface->is_licensed(pszLicense, pszUserId);
}

void netnodeScriptComposite::menuleft_printVert001(ui_menu * pmenu, int iPanelIndex)
{
   return m_pinterface->menuleft_printVert001(pmenu, iPanelIndex);
}

string netnodeScriptComposite::web_map(const char * psz)
{
   return m_pinterface->web_map(psz);
}

bool netnodeScriptComposite::is_site_user(var varSite, var varUser)
{
   return m_pinterface->is_site_user(varSite, varUser);
}

bool netnodeScriptComposite::is_site_user(var varSite)
{
   return m_pinterface->is_site_user(varSite);
}

string netnodeScriptComposite::low_fs_file_path(const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension)
{
   return m_pinterface->low_fs_file_path(hash, key, size, mimetype, extension);
}

bool netnodeScriptComposite::low_fs_read(const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension)
{
   return m_pinterface->low_fs_read(hash, key, size, mimetype, extension);
}

bool netnodeScriptComposite::low_fs_read(const char * user, __int64 iFolder, const char * pszName)
{
   return m_pinterface->low_fs_read(user, iFolder, pszName);
}


__int64 netnodeScriptComposite::low_fs_map(const char * pszDir)
{
   return m_pinterface->low_fs_map(pszDir);
}

bool netnodeScriptComposite::low_fs_map_file(const char * pszPath)
{
   return m_pinterface->low_fs_map(pszPath);
}

bool netnodeScriptComposite::low_fs_license(const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension)
{
   return m_pinterface->low_fs_license(user, hash, key, size, mimetype, extension);
}

bool netnodeScriptComposite::low_fs_is_licensed(const char * user, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension)
{
   return m_pinterface->low_fs_is_licensed(user, hash, key, size, mimetype, extension);
}

bool netnodeScriptComposite::low_fs_add_user_file(const char * user, __int64 iFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char * pszName, bool bOverwrite)
{
   return m_pinterface->low_fs_add_user_file(user, iFolder, hash, key, size, mimetype, extension, pszName, bOverwrite);
}

__int64 netnodeScriptComposite::low_fs_add_user_dir(const char * user, __int64 iParentFolder, const char * pszName)
{
   return m_pinterface->low_fs_add_user_dir(user, iParentFolder, pszName);
}

void netnodeScriptComposite::low_fs_ls_dir(const char * user, __int64 iParentFolder, int64_array & ia, stringa & stra)
{
   return m_pinterface->low_fs_ls_dir(user, iParentFolder, ia, stra);
}

void netnodeScriptComposite::low_fs_ls_file(const char * user, __int64 iFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName)
{
   return m_pinterface->low_fs_ls_file(user, iFolder, straHash, iaKey, iaSize, straMime, straExt, straName);
}

bool netnodeScriptComposite::low_folder(string & strUser, __int64 & iFolder, const char * pszFolder)
{
   return m_pinterface->low_folder(strUser, iFolder, pszFolder);
}

bool netnodeScriptComposite::fs_dir_mk(const char * pszFolder)
{
   return m_pinterface->fs_dir_mk(pszFolder);
}

int netnodeScriptComposite::datetime_get_month_day_count(int year, int month)
{
   return m_pinterface->datetime_get_month_day_count(year, month);
}

// 0 is Sunday
string netnodeScriptComposite::datetime_get_weekday(int year, int month, int day)
{
   return m_pinterface->datetime_get_weekday(year, month, day);
}

class time netnodeScriptComposite::datetime_get_timestamp(int year, int  month,  int day)
{
   return m_pinterface->datetime_get_timestamp(year, month, day);
}

string netnodeScriptComposite::datetime_getGMTDateTime()
{
   return m_pinterface->datetime_getGMTDateTime();
}

string netnodeScriptComposite::datetime_formatDateTime(class time t)
{
   return m_pinterface->datetime_formatDateTime(t);
}

class time netnodeScriptComposite::datetime_getTimestamp()
{
   return m_pinterface->datetime_getTimestamp();
}

__int64 netnodeScriptComposite::datetime_InternationalToUnixMillis(const char * date)
{
   return m_pinterface->datetime_InternationalToUnixMillis(date);
}

string netnodeScriptComposite::datetime_getToday()
{
   return m_pinterface->datetime_getToday();
}

class time netnodeScriptComposite::datetime_strtotime(const char * psz)
{
   return m_pinterface->datetime_strtotime(psz);
}

class time netnodeScriptComposite::datetime_strtotime(const char * psz, class time t)
{
   return m_pinterface->datetime_strtotime(psz, t);
}

