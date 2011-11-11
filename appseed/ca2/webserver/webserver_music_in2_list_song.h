#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca in2_list_song :
         virtual public in2_list
      {
      public:
         var m_title;
         var m_songcount;
         var m_query;
         var m_lyrics;
         var m_cid;
         var m_aid;
         var m_performername;
         var m_classname;
         var m_styletitle;
         var m_db;
         webserver::music::performer * m_pperformer;
         webserver::music::performer * m_previous_artist;
         webserver::music::performer * m_next_artist;
         webserver::music::performer_ptr_array * m_partista;
         var m_topictype;

         in2_list_song(
            var query,
            var song, 
            var lyrics, 
            var querystyle, 
            var order, 
            int curpage, 
            int limitcount,
            var cid,
            var aid, 
            var target,
            var funuid,
            gen::property_set & params,
            var call_url);

         virtual void print_js_include();
         virtual string   get_title();
         virtual void print_slist_preamble();
         virtual void print_list();
         virtual void song_starttable();
         virtual void printrows();
         virtual void song_printrows();
         virtual void print_row(webserver::music:: song * psong, var line);
         virtual void song_endtable();
         virtual void print_slist_closure();
         virtual var get_accept_params();
         virtual string multi_page_get_nav_link_text_append(var page);
      };

   } // namespace music


} // namespace webserver