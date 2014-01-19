
#undef __id
#define __id(x) (m_pbaseapp->m_pbasesystem->m_cidpool.id_##x)



class CLASS_DECL_BASE id_pool
{
public:

   id id_eu;
   id id_uk;
   id id_fi;
   id id_gr;
   id id_nl;
   id id_be;
   id id_it;
   id id_cz;


   id id_dk;
   id id_en_uk;
   id id_lu;
   id id_ie;
   id id_no;
   id id_cy;
   id id_su;
   id id_lv;
   id id_li;
   id id_hu;
   id id_sk;
   id id_si;
   id id_ro;
   id id_kz;
   id id_ru;
   id id_pl;
   id id_tr;
   id id_ee;
   id id_asia;
   id id_vn;
   id id_in;
   id id_kg;
   id id_kr;
   id id_my;
   id id_ph;
   id id_sg;


   id id_zh;
   id id_sy;
   id id_ps;
   id id_ar;
   id id_bo;
   id id_cl;
   id id_co;
   id id_gs;
   id id_py;
   id id_uy;
   id id_ve;
   id id_amdesur;
   id id_au;
   id id_oceania;
   id id_nz;
   id id_tl;
   id id_ug;
   id id_sc;
   id id_cm;
   id id_za;
   id id_africa;
   id id_us;
   id id_caribe;
   id id_ht;
   id id_cu;
   id id_tc;
   id id_centralam;
   id id_bz;
   id id_america;

   id id_cc;
   id id_se;
   id id_sv_se;
   id id_sv;


   id id_at;
   id id_de_at;
   id id_de;
   id id_de_de;

   id id_br;
   id id_pt_br;
   id id_pt;

   id id_es;

   id id_cn;
   id id_zh_cn;
   id id_zh_tw;
   id id_hk;

   id id_ja;
   id id_jp;
   id id_ja_jp;

   id id_fr;
   id id_fr_ca;
   id id_ca;

   id id_en;
   id id_en_us;
   id id_en_ca;
   id id_std;

   id id_pe;
   id id_mx;
   id id_ec;

   id id_tw;

   id id_earth;
   id id_vg;
   id id_ae;
   id id_il;


   id id_http_host;
   id id_http_version;
   id id_http_status_code;
   id id_http_status;
   id id_http_method;
   id id_http_protocol;
   id id_http_referer;
   id id_https;

   id id_query_string;

   id id_content_length;
   id id_content_type;
   id id_connection;
   id id_location;
   id id_set_cookie;
   id id_cookie;
   id id_cache_control;
   id id_pragma;
   id id_expires;
   id id_host;
   id id_referer;

   id id_close;

   id id_put;

   id id_remote_addr;
   id id_request_uri;

   id id_accept_encoding;
   id id_content_encoding;

   id id_keep_alive;

   id id_user_agent;
   id id_from;
   id id_accept_language;


   id id_accept;


   id_pool()
   {

      reset();

   }


   void reset() const
   {
      (const_cast < id_pool * > (this))->_reset();
   }


protected:

   void _reset();

};
