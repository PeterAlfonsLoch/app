#include "framework.h"


class ::id base_system::idEmpty;
class ::id_space * base_system::s_pidspace = NULL;


base_system::base_system(sp(base_application) papp) :
   m_urldepartament(this),
   //m_mutexDelete(this),
   m_httpsystem(this),
   m_net(this)
   //m_mutex(this),
#ifndef METROWIN
   //m_processsection(this),
#endif
   //m_visual(this)
{


   m_psimpleui = NULL;

#ifdef METROWIN
   m_posdata = new os_data();
#endif

   set_app(this);

   m_pbasesystem = this;

   if(papp == NULL)
   {

      oprop("parent_system") = (sp(element)) NULL;

   }
   else
   {

      oprop("parent_system") = papp->m_pbasesystem;

   }



   //::ca::application::m_file.set_app(this);
   //::ca::application::m_dir.set_app(this);

   string strId;
   //strId = m_strAppName;
   //strId += ::str::has_char(m_strAppId, ".");
   //strId += ::str::has_char(m_strBaseSupportId, ".");


   strId = "ca2log";

   
   xxdebug_box("Going to start Log", "Just before initialize log", 0);

   // log starts here
   if(!initialize_log(strId))
   {
   xxdebug_box("Could not initialize log", "Failed to initialize log", 0);
   throw "failed to initialize log";
   }

   
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


   //use_base_ca2_allocator();


   m_pfactory = new class base_factory(this);
   m_pfactory->set_app(this);

   m_spinstall = new ::install::install(this);


#ifdef WINDOWS
   m_pmutexDc = NULL;
   m_pdevicecontext = NULL;
#endif


   Ex1OnFactoryExchange();

   //m_spfilesystem.create(allocer());


   {

      draw2d_gdiplus::factory_exchange factoryexchange(this);

   }

   m_pxml = canew(::xml::departament(this));

   m_pxml->construct(this);

   if (!m_pxml->initialize1())
      throw simple_exception(this, "failed to construct base_system");

   if (!m_pxml->initialize())
      throw simple_exception(this, "failed to construct base_system");

}


void base_system::construct()
{

   ::base_application::construct();

   m_spos.create(allocer());

   m_spfile.create(allocer());
   m_spdir.create(allocer());


   if (!m_spdir->initialize())
      throw simple_exception(this, "failed to construct base_system");



}
base_factory & base_system::factory()
{
   return *m_pfactory;
}


::exception::engine & base_system::eengine()
{

   static ::exception::engine s_eengine(NULL);

   return s_eengine;

}


bool base_system::process_initialize()
{

   m_pfactory->cloneable_large < create_context > ();
   m_pfactory->cloneable_large < application_bias > ();
   m_pfactory->cloneable_large < command_line > ();
   m_pfactory->cloneable_large < manual_reset_event > ();
   m_pfactory->cloneable_large < mutex > ();
   m_pfactory->cloneable_large < event > ();
   m_pfactory->creatable_large < ::file::simple_binary_buffer > (type_info < ::file::binary_buffer >());
   m_pfactory->creatable_large < ::file::string_buffer > ();




   return true;

}




bool base_system::initialize_instance()
{

   m_pfactory->enable_simple_factory_request();

   return true;

}


UINT base_system::os_post_to_all_threads(UINT uiMessage, WPARAM wparam, lparam lparam)
{

   throw interface_only_exception(this);


}

sp(element) base_system::clone()
{
   // by the time, it is not possible to clone a base_system
   return NULL;
}

sp(element) base_system::clone(sp(element) pobj)
{
   return System.factory().base_clone(pobj);
}


void base_system::discard_to_factory(sp(element) pca)
{

   if(m_pfactory == NULL)
      return;

   m_pfactory->discard(pca);

}



void base_system::wait_twf()
{

}

bool base_system::is_system()
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
   id_fr_ca = "fr-core";
   id_ca = "ca2";

   id_en = "en";
   id_en_us = "en-us";
   id_en_ca = "en-core";
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





bool base_system::assert_failed_line(const char * lpszFileName, int32_t iLine)
{
   UNREFERENCED_PARAMETER(lpszFileName);
   UNREFERENCED_PARAMETER(iLine);
   return false;
}


bool base_system::on_assert_failed_line(const char * lpszFileName, int32_t iLine)
{
   UNREFERENCED_PARAMETER(lpszFileName);
   UNREFERENCED_PARAMETER(iLine);
   return true;
}




sp(element) base_system::on_alloc(sp(base_application) papp, sp(type) info)
{
   /*string str;
   str.Format("Could not alloc %s", info.name());
   simple_message_box(str);*/
   sp(element) pobj = m_pfactory->create(papp, info);
   if(pobj != NULL)
      return pobj;
   on_allocation_error(papp, info);
   return NULL;
}

sp(element) base_system::alloc(sp(base_application) papp, sp(type) info)
{
   return on_alloc(papp, info);
}

sp(element) base_system::alloc(sp(base_application) papp, const std_type_info & info)
{
   return on_alloc(papp, canew(type(info)));
}

void base_system::on_allocation_error(sp(base_application) papp, sp(type) info)
{
   UNREFERENCED_PARAMETER(papp);
   UNREFERENCED_PARAMETER(info);
}

sp(element) base_system::alloc(sp(base_application) papp, const class id & idType)
{
   return on_alloc(papp, get_type_info(idType));
}


sp(type) base_system::get_type_info(const ::std_type_info & info)
{

#ifdef WINDOWS
   sp(type) & typeinfo = m_typemap[info.raw_name()];
#else
   sp(type) & typeinfo = m_typemap[info.name()];
#endif

   if(typeinfo.is_null())
      typeinfo = canew(type(info));

   return typeinfo;

}


::xml::departament & base_system::xml()
{
   return *m_pxml;
}



class ::str::base64 & base_system::base64()
{

   return m_base64;

}





::sockets::net & base_system::net()
{
   return m_net;
}



class ::crypto::crypto & base_system::crypto()
{
   return *m_spcrypto;
}



::datetime::departament & base_system::datetime()
{
   return *m_pdatetime;
}



sp(::user::window_draw) base_system::get_twf()
{

   return m_ptwf;

}

::core::log & base_system::log()
{
   return *m_plog;
}




::fontopus::user_set & base_system::userset()
{
   return m_userset;
}



::core::compress & base_system::compress()
{
   return m_compress;
}



machine_event_central & base_system::machine_event_central()
{
   return *m_pmachineeventcentral;
}


::user::str & base_system::str()
{

   return *m_puserstr;

}


sp(::user::object) base_system::place_hold(sp(::user::interaction) pui)
{


   //if(m_pcubeInterface != NULL)
   //{
     // return m_pcubeInterface->hold(pui);
   //}

   return NULL;

}


sp(::base_session) base_system::query_session(index iEdge)
{

   return NULL;

}


::core::os & base_system::os()
{

   return *m_spos;

}




bool base_system::initialize_log(const char * pszId)
{
   if (m_plog != NULL)
      return true;
   m_plog = new ::core::log(this);
   m_plog->set_extended_log();
   m_plog->set_app(this);
   if (!m_plog->initialize(pszId))
   {
      m_plog.release();
      return false;
   }
   //      ::core::trace_v = &::core::system_log_trace_v;
   return true;
}


application_ptra & base_system::appptra()
{
   return m_appptra;
}

