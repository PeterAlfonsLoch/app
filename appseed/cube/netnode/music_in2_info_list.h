#pragma once



namespace music
{

   class CLASS_DECL_CA2_CUBE in2_info_list :
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
      virtual void print_td(int i = 0, const char * prefix_style = "");
   
      virtual int get_cur_song_index();

      virtual ::music::song * get_cur_song();
   
      virtual bool is_selected(::music::song * psong, int iIndex);

      virtual void print_slist_closure();

      virtual void print_row(int iIndex, ::music::song * psong, int iLine) = 0;
   }
   ;
} // namespace music