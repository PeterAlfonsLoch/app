#pragma once


namespace webserver
{

   namespace music
   {

      class CLASS_DECL_ca in2_info_list :
         public in2_list
      {
      public:
         var m_sheetcount;
         int m_cur_pgid;
         var m_cur_topic;
         var m_cur_topictype;

         in2_info_list();

         in2_info_list(var songid, var pgid, var topic, var topictype);

         virtual void print_list();
   
         virtual string get_list_title();
   
         virtual void starttable();
      
         virtual void endtable();
   
         virtual void printrows();

         using in2_list::print_td;
         virtual void print_td(index i = 0, const char * prefix_style = "");
   
         virtual index get_cur_song_index();

         virtual ::webserver::music::song * get_cur_song();
   
         virtual bool is_selected(::webserver::music::song * psong, index iIndex);

         virtual void print_slist_closure();

         virtual void print_row(index iIndex, ::webserver::music::song * psong, index iLine) = 0;


      };


   } // namespace music


} // namespace webserver


