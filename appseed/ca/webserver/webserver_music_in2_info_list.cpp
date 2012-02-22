#include "StdAfx.h"

namespace webserver
{

namespace music
{

   in2_info_list::in2_info_list()
   {
   }


   in2_info_list::in2_info_list(var songid, var pgid, var topic, var topictype)
   {
      //global $musicdb;
      //global $g_listline;

      if(!gprop("g_listline").is_set())
         gprop("g_listline") = 0;

      ::index limitstart = 0;
      ::count limitcount = 1000;
      ::index lastpage= 0;
      ::count totalcount= 0;
      string order = "";
      string querystyle_arg = "";
      string lyrics = "";
      dprint("SID=" + songid);
      string sql;
      if(strlen(songid) == 0)
      {
         sql = "SELECT song FROM topic_song WHERE topic = $topic AND topictype = $topictype";
         songid = musicdb().query_item(sql);
      }
      var query = "";
      var req_params = "";
      m_psonga = musicdb().get_songs(req_params,
         query,
         songid,
         lyrics,
         querystyle_arg,
         order,
         limitstart,
         limitcount,
         lastpage,
         totalcount,
         get("cid"),
         get("aid"),
         topictype,
         NULL,
         NULL);
      m_cur_pgid = pgid;
      m_cur_topic = topic;
      m_cur_topictype = topictype;
      dprint("CurTopic=" + m_cur_topic);
      dprint("CurTopicType=" + m_cur_topictype);
   }

   void in2_info_list::print_list()
   {
//         m_printSListPreamble();
      starttable();
      printrows();
      endtable();
      print_slist_closure();
   }

   string in2_info_list::get_list_title()
   {
      return "";
   }

   void in2_info_list::starttable()
   {
      print("<div class='songinfolist3'>");
      print ("<div class='songinfolist2'>");
      print ("<div class='songinfolist1'>");
      print ("<span class='songinfolist-title'>");
      print( get_list_title());
      print ("</span>");
      print ("<table border='0' width='100%'>");
      print ("<tbody>");
   }
   void in2_info_list::endtable()
   {
      print( "</tbody>");
      print ("</table>");
      print( "</div>"); // songinfolist1
      print ("</div>"); // songinfolist2
      print ("</div>"); // songinfolist3
   }

   void in2_info_list::printrows()
   {
      //global $g_listline;
      ::count count = m_psonga->get_count();
      m_cur_line = 0;
//         print "count=$count";
      for(index i = 0; i < count; i++)
      {

         print_row(i, m_psonga->element_at(i), gprop("g_listline"));
         gprop("g_listline")++;
         m_cur_line++;
      }
//      m_song_printrows();
   }

   void in2_info_list::print_td(index i1, const char * prefix_style)
   {
      UNREFERENCED_PARAMETER(i1);
      string style;
      if((m_cur_line % 2) == 0)
      {
         style = "i0-td";
      }
      else
      {
         style = "i1-td";
      }
      style = gen::str::has_char(style, prefix_style);
      print("<td class='infoi "+style+"'>");
   }

      index in2_info_list::get_cur_song_index()
      {
         ::count count = m_psonga->get_count();
         for(index i = 0; i < count; i++)
         {
            if(is_selected(m_psonga->element_at(i), i))
               return i;
         }
         return -1;
      }

      ::webserver::music::song * in2_info_list::get_cur_song()
      {
         index index = get_cur_song_index();
         if(index >= 0)
            return m_psonga->element_at(index);
         else
            return NULL;
      }

      bool in2_info_list::is_selected(::webserver::music::song * psong, index index)
      {
         dprint("List:selected?");
         bool selected;
         if(m_cur_pgid > 0)
         {
            selected = (index + 1) == m_cur_pgid;
         }
         else
         {
            dprint("Topic=" + psong->m_propertyset["topic"]);
            dprint("TopicType=" + psong->m_propertyset["topictype"]);
            selected = psong->m_propertyset["topic"] == m_cur_topic
                  && psong->m_propertyset["topictype"] == m_cur_topictype;
         }
         if(selected)
         {
            dprint("Yes");
         }
         else
         {
            dprint("No");
         }
         return selected;
      }

      void in2_info_list::print_slist_closure()
      {
         //global $g_nosong_extra;
         dprint("tr_mdwn COUNT=" + count(m_tr_mdwn_parama));
         //dprint_r(m_tr_mdwn_parama);
         tr_mdwn_parama_endtable();
      }

} // namespace music


} // namespace webserver
