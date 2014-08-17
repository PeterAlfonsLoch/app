
#undef __id
#define __id(x) (m_pbaseapp->m_pbasesystem->m_cidpool.id_##x)



class CLASS_DECL_AXIS id_pool
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



   id id_html_none;
   id id_html_unknown;
   id id_html_new;
   id id_html_initial;
   id id_html_html;
   id id_html_head;
   id id_html_title;
   id id_html_meta;
   id id_html_link;
   id id_html_style;
   id id_html_script;
   id id_html_body;
   id id_html_span;
   id id_html_h1;
   id id_html_h2;
   id id_html_h3;
   id id_html_h4;
   id id_html_h5;
   id id_html_p;
   id id_html_table;
   id id_html_tbody;
   id id_html_tr;
   id id_html_td;
   id id_html_div;
   id id_html_br;
   id id_html_form;
   id id_html_input;
   id id_html_select;
   id id_html_option;
   id id_html_img;
   id id_html_font;
   id id_html_li;
   id id_html_a;
   id id_html_strong;


   id id_html_class;

   
   id id_html_display;
   id id_html_margin;
   id id_html_border;
   id id_html_padding;

   id id_html_block;
   id id_html_inline;
   id id_html_table_row;
   id id_html_table_cell;

   id id_html_margin_left;
   id id_html_margin_top;
   id id_html_margin_right;
   id id_html_margin_bottom;
   id id_html_border_left;
   id id_html_border_top;
   id id_html_border_right;
   id id_html_border_bottom;
   id id_html_padding_left;
   id id_html_padding_top;
   id id_html_padding_right;
   id id_html_padding_bottom;


   id id_html_css_suffix_left;
   id id_html_css_suffix_top;
   id id_html_css_suffix_right;
   id id_html_css_suffix_bottom;

   id id_html_css_suffix_width;
   id id_html_css_suffix_left_width;
   id id_html_css_suffix_top_width;
   id id_html_css_suffix_right_width;
   id id_html_css_suffix_bottom_width;

   id id_html_css_suffix_color;
   id id_html_css_suffix_left_color;
   id id_html_css_suffix_top_color;
   id id_html_css_suffix_right_color;
   id id_html_css_suffix_bottom_color;


   id id_html_border_width;
   id id_html_border_left_width;
   id id_html_border_top_width;
   id id_html_border_right_width;
   id id_html_border_bottom_width;

   id id_html_border_color;
   id id_html_border_left_color;
   id id_html_border_top_color;
   id id_html_border_right_color;
   id id_html_border_bottom_color;


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
