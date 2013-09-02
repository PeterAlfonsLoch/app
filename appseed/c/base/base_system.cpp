#include "framework.h"


system::system(sp(::application) papp) :
   m_urldepartament(this)
   //m_mutexDelete(this),
   //m_http(this),
   //m_net(this),
   //m_mutex(this),
#ifndef METROWIN
   //m_processsection(this),
#endif
   //m_visual(this)
{


#ifdef METROWIN
   m_window                                  = nullptr;
#endif
#ifdef WINDOWS
   //      m_pmutexDc                                = NULL;
   //    m_pdevicecontext                          = NULL;
#endif

   //m_psystem                                 = this;
   m_pcasystem                                 = this;
   set_app(this);


   if(papp == NULL)
   {

      oprop("parent_system") = (sp(element)) NULL;

   }
   else
   {

      oprop("parent_system") = papp->m_pcasystem;

   }


   //::ca::application::m_file.set_app(this);
   //::ca::application::m_dir.set_app(this);

   //      m_bDoNotExitIfNoApplications              = true;

   string strId;
   //strId = m_strAppName;
   //strId += ::str::has_char(m_strAppId, ".");
   //strId += ::str::has_char(m_strBaseSupportId, ".");


   strId = "ca2log";

   /*
   xxdebug_box("Going to start Log", "Just before initialize log", 0);

   // log starts here
   if(!initialize_log(strId))
   {
   xxdebug_box("Could not initialize log", "Failed to initialize log", 0);
   throw "failed to initialize log";
   }

   */
   /*
   if(psystemParent == NULL)
   {

   m_peengine                                = new ::exception::engine(this);

   }
   else
   {

   m_peengine                                = psystemParent->m_peengine;

   }
   */


   if(::get_heap_mutex() == NULL)
   {

      ::set_heap_mutex(new mutex(this));

   }

   use_base_ca2_allocator();


   m_pfactory = new class factory(this);
   m_pfactory->set_app(this);

   m_pfactory->cloneable_large < create_context > ();
   m_pfactory->cloneable_large < application_bias > ();
   m_pfactory->cloneable_large < command_line > ();
   m_pfactory->cloneable_large < manual_reset_event > ();
   m_pfactory->cloneable_large < mutex > ();
   m_pfactory->cloneable_large < event > ();

}

factory & system::factory()
{
   return *m_pfactory;
}


::exception::engine & system::eengine()
{

   static ::exception::engine s_eengine(NULL);

   return s_eengine;

}


bool system::initialize_instance()
{

   m_pfactory->enable_simple_factory_request();

   return true;

}


UINT system::os_post_to_all_threads(UINT uiMessage, WPARAM wparam, lparam lparam)
{

   throw interface_only_exception(this);


}

sp(element) system::clone()
{
   // by the time, it is not possible to clone a system
   return NULL;
}

sp(element) system::clone(sp(element) pobj)
{
   return System.factory().base_clone(pobj);
}


void system::discard_to_factory(sp(element) pca)
{

   if(m_pfactory == NULL)
      return;

   m_pfactory->discard(pca);

}


bool system::process_initialize()
{

   m_pxml = canew(::xml::departament(this));

   m_pxml->construct(this);

   if(!m_pxml->initialize1())
      return false;

   if(!m_pxml->initialize())
      return false;


   return true;

}


void system::wait_twf()
{
   
}

bool system::is_system()
{

   return true;

}




void id_pool::_reset()
{


   id_eu = "eu";
   id_uk = "uk";
   id_fi = "fi";
   id_gr = "gr";
   id_nl = "nl";
   id_be = "be";
   id_it = "it";
   id_cz = "cz";

   id_dk = "dk";
   id_en_uk = "en-uk";
   id_lu = "lu";
   id_ie = "ie";
   id_no = "no";
   id_cy = "cy";
   id_su = "su";
   id_lv = "lv";
   id_li = "li";
   id_hu = "hu";
   id_sk = "sk";
   id_si = "si";
   id_ro = "ro";
   id_kz = "kz";
   id_ru = "ru";
   id_pl = "pl";
   id_tr = "tr";
   id_ee = "ee";
   id_asia = "asia";
   id_vn = "vn";
   id_in = "in";
   id_kg = "kg";
   id_kr = "kr";
   id_my = "my";
   id_ph = "ph";
   id_sg = "sg";


   id_zh = "zh";
   id_sy = "sy";
   id_ps = "ps";
   id_ar = "ar";
   id_bo = "bo";
   id_cl = "cl";
   id_co = "co";
   id_gs = "gs";
   id_py = "py";
   id_uy = "uy";
   id_ve = "ve";
   id_amdesur = "amdesur";
   id_au = "au";
   id_oceania = "oceania";
   id_nz = "nz" ;
   id_tl = "tl" ;
   id_ug = "ug" ;
   id_sc = "sc" ;
   id_cm = "cm" ;
   id_za = "za" ;
   id_africa = "africa";
   id_us = "us";
   id_caribe = "caribe";
   id_ht = "ht" ;
   id_cu = "cu" ;
   id_tc = "tc" ;
   id_centralam = "centralam";
   id_bz = "bz";
   id_america = "america";

   id_cc = "cc";
   id_se = "se";
   id_sv_se = "sv-se";
   id_sv = "sv";

   id_at = "at";
   id_de_at = "de-at";
   id_de = "de";
   id_de_de = "de-de";

   id_br = "br";
   id_pt_br = "pt-br";
   id_pt = "pt";

   id_es = "es";

   id_cn = "cn";
   id_zh_cn = "zh-cn";
   id_zh_tw = "zh-tw";
   id_hk = "hk";

   id_ja_jp = "ja-jp";
   id_ja = "ja";
   id_jp = "jp";

   id_fr = "fr";
   id_fr_ca = "fr-ca2";
   id_ca = "ca2";

   id_en = "en";
   id_en_us = "en-us";
   id_en_ca = "en-ca2";
   id_std = "_std";

   id_pe = "pe";
   id_mx = "mx";
   id_ec = "ec";

   id_tw = "tw";

   id_earth = "earth";
   id_vg = "vg";
   id_ae = "ae";
   id_il = "il";



   id_http_host = "http_host";
   id_http_version = "http_version";
   id_http_status_code = "http_status_code";
   id_http_status = "http_status";
   id_http_method = "http_method";
   id_http_protocol = "http_protocol";
   id_http_referer = "http_referer";
   id_https = "https";

   id_query_string = "query_string";

   id_content_length = "content-length";
   id_content_type = "content-type";
   id_connection = "connection";
   id_location = "location";
   id_set_cookie = "set-cookie";
   id_cookie = "cookie";
   id_cache_control = "cache-control";
   id_pragma = "pragma";
   id_expires = "expires";
   id_host = "host";
   id_referer = "referer";

   id_close = "close";

   id_put = "put";

   id_remote_addr = "remote_addr";
   id_request_uri = "request_uri";

   id_accept_encoding = "accept-encoding";
   id_content_encoding = "content-encoding";

   id_keep_alive = "keep-alive";

   id_user_agent = "user-agent";
   id_from = "from";
   id_accept_language = "accept-language";


   id_accept = "accept";

}
