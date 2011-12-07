#pragma once


namespace webserver
{


   namespace music
   {
      class CLASS_DECL_ca in2_list :
         virtual public dynamic_source::ptr
      {
      public:
         var m_order;
         var m_db;
         var m_thislist; // Parent List id
         var m_thisnav; // Parent List id
         var m_parentlist; // Parent List id
         var m_parentnav; // Parent List id
         var m_listtitle;
         var m_id;
         var m_navtitle;
         var m_dataa;
         var m_params_ex;
         var m_tr_mdwn_parama;
         var m_formatstyle;

         gen::property_set m_params;

         var m_target;   

         var m_call_url;
         var m_base_url_path;

         // Multiple pages   
         int m_curpage;
         int m_lastpage;
         int m_limitcount;
         int m_totalcount;
         int m_num_rows;

         // song
         webserver::music::song_ptr_array * m_psonga;
         webserver::music::song_ptr_array * m_psonga2;
         var m_perf_perf_glue;
         var m_perf_glue;
         var m_perf_perf_last_glue;
         var m_bFirstPerf;

         var m_querystyle;
         var m_bAsc;

         int m_cur_line;


         virtual string get_list_title();


         in2_list();
         in2_list(var target, var order = "", var params_ex = gen::g_newconst, gen::property_set params = gen::property_set());


         virtual void print_css_include();

         virtual string bold001(var text);

         virtual void print_tr(var mainlink, var param = gen::g_newconst);
         virtual void print_td(var i1 = 0, var prefix_style = "");
         virtual void performer_starttable();
         virtual void print_out_nav(var linka, var titlea);
         virtual void performer_endtable();
         virtual void tr_mdwn_parama_endtable();
         virtual void print_js_include();
         virtual string get_title();
         virtual void print_navigation(var nav);
         virtual void songa_print_kar_warning();
         virtual var get_kar_warning_path_list();
         virtual void multi_page_init(int curpage, int limitcount);
         virtual void multi_page_inst(int totalcount, int num_rows, int lastpage);
         virtual void print_multi_page_nav(bool bInMulti = false);
         virtual int multi_page_get_list_first_page();
         virtual int multi_page_get_list_last_page();
         virtual int multi_page_get_limit_back_advance();
         virtual int multi_page_get_limit_start();
         virtual int multi_page_get_result_start();
         virtual int multi_page_get_result_end();
         virtual int multi_page_get_limit_advance();
         virtual string multi_page_get_nav_link(var page);
         virtual string multi_page_get_nav_link_text_append(var page);
         virtual int multi_page_get_item_start();
         virtual int multi_page_get_item_end();
         virtual int multi_page_map_to_internal_item(int item);

         // getTitle   
         // printSListPreamble
         // printList
         // printSListClosure

         virtual void print_slist_closure();

         virtual var get_accept_params();

         virtual void _set_params(gen::property_set & params);

         virtual bool has_param(var paramName);


         virtual void print_kar_warning(const char * path);


      };


   } // namespace music


} // namespace webserver

