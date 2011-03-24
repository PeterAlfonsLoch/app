#include "StdAfx.h"

namespace music
{

      karaoke_song_in2_list::karaoke_song_in2_list(var id)
      {
         //global $musicdb;
         m_psonga = musicdb().get_song_files(id);
      }

      string karaoke_song_in2_list::get_list_title()
      {
         return pstr("list:karaokesong:listtitle1");
      }
      
      void karaoke_song_in2_list::print_list()
      {
//         m_printSListPreamble();
         starttable();
         printrows();
         endtable();
         print_slist_closure();
      }
      
      
   
      void karaoke_song_in2_list::printrows()
      {
         //global $g_listline;
         //$songa =   &m_songa;
         for(index i = 0; i < m_psonga->get_count(); i++)
         {
            print_row(i, m_psonga->element_at(i), gprop("g_listline"));
            gprop("g_listline")++;
         }
   //      m_song_printrows();
      }
      
      void karaoke_song_in2_list::print_row(int iIndex, ::music::song * psong, int iLine)
      {
         UNREFERENCED_PARAMETER(iIndex);
         //global $musicdb;
//         $savelink = ui_url('download?filename='.$song->filename.'&referer='.urlencode($_SERVER['REQUEST_URI']));
         string savelink = ui_url("/file/download/" + psong->m_propertyset["filename"]);
         string openlink    =    "javascript:open_kar_file('"+urlencode("file/open/" + psong->m_propertyset["filename"]) + "')";
         string mainlink;
         if(get("fwdaction").is_set())
         {
            mainlink = ui_url(get("fwdaction") + "?topic=" + psong->m_propertyset["topic"] + "&topictype=" + psong->m_propertyset["topictype"]);
         }
         else
         {
            mainlink = openlink;      
         }

         string line = gen::str::itoa(iLine);
         
//         $openlink = "/open/download/".$song->filename;
          string type       = psong->m_propertyset["type"];
   
         
         print_tr(mainlink);
//         m_tr_mdwn_parama[$line] = $mainlink;
         
         
         print_td(-1);
         print(psong->m_propertyset["title"]);
         print ("</td>");
         
         print_td(-1);
         print ("<img src=\"" + music().song_get_song_type_image1(type) + "\">");
         print ("</td>");
         
         
         print_td(-1);
         print("<a href='"+savelink+"'>");
         print("<img class='i1il' name='saveImg" + line +"'   src='" + simage("sd1n") + "'   title=\"\" alt=\"\" id='saveImg" +line + "'   align='left' border='0'>\n");
         print(pstr("song.info.general:Sparar/Ladda ner"));
         print("</a>");
         print("</td>");

         print_td(-1);
         print("<a href=\""+openlink+"\">");
         print("<img class='i1il' name='openImg" +line + "' src='" + simage("sp1n") + "' title=\"\" alt=\"\" id='openImg" +line + "' align='left' border='0'>\n");
         print(langstr("song.info.general:open/Play"));
         print ("</a>");
         print ("</td>");

         ::fun::user * pinsertion_user = fun().get_user(psong->m_propertyset["insertionuserid"]);
         ::music::song_source * psong_source = musicdb().get_song_source(psong->m_propertyset["insertionsourceid"]);
         print("</tr>");
           print ("\n");
         print ("<tr>");
         print ("<td class=\"slist-comment-label\">");
         print(pstr("karaoke.song.list:file.insertion.datetime"));
         print("</td>");
         print("<td colspan=\"4\" class=\"slist-comment-value\">");
         print(psong->m_propertyset["insertiondatetime"]);
         print("</td>");
         print("</tr>");
         string value = pinsertion_user->m_strFirstName + " " + pinsertion_user->m_strLastName;
         value.trim();
         if(value.has_char())
         {
            print("<tr>");
            print("<td class=\"slist-comment-label\">");
            print(pstr("karaoke.song.list:file.insertion.user"));
            print("</td>");
            print("<td colspan=\"4\" class=\"slist-comment-value\">");
            print("<a href=\"/fun?Home({$insertion_user->id})\">");
            print(pinsertion_user->m_strFirstName + " " + pinsertion_user->m_strLastName);
            print("</a>");
            print("</td>");
            print( "</tr>");
            print ("\n");
         }
         if(psong_source == NULL)
            value.Empty();
         else
            value = psong_source->m_strName;
         value.trim();
         if(value.has_char())
         {
            print("<tr>");
            print("<td class=\"slist-comment-label\">");
            print(pstr("karaoke.song.list:file.source"));
            print("</td>");
            print("<td colspan=\"4\" class=\"slist-comment-value\">");
            print("<a href=\"" + psong_source->m_strUrl + "\">");
            print(psong_source->m_strName);
            print("</a>");
            print("</td>");
            print("</tr>");
            print("\n");
         }
         value = psong->m_propertyset["insertercomment"];
         value.trim();
         if(value.has_char())
         {
            print("<tr>");
            print("<td class=\"slist-comment-label\">");
            print(pstr("karaoke.song.list:file.insertercomment"));
            print("</td>");
            print("<td colspan=\"4\" class=\"slist-comment-value\">");
            print("<a href=\"{$song->insertercomment}\">");
            print(psong->m_propertyset["insertercomment"]);
            print("</a>");
            print("</td>");
            print("</tr>");
            print("\n");
         }
         value = psong->m_propertyset["insertionsourcecomment"];
         value.trim();
         if(value.has_char())
         {
            print("<tr>");
            print("<td class=\"slist-comment-label\">");
            print(pstr("karaoke.song.list:file.insertionsourcecomment"));
            print("</td>");
            print("<td colspan=\"4\" class=\"slist-comment-value\">");
            print(psong->m_propertyset["insertionsourcecomment"]);
            print("</td>");
            print("</tr>");
            print("\n");
         }
      
      }
   void karaoke_song_in2_list::print_slist_closure()
   {
      //global $g_nosong_extra;
      dprint("tr_mdwn COUNT=" + count(m_tr_mdwn_parama));
      //dprint_r(m_tr_mdwn_parama);
      tr_mdwn_parama_endtable();
      if(!isset(get("fwdaction")))
      {
         if(gprop("g_nosong_extra") != 1)
         {
            songa_print_kar_warning();
         }
      }
   }
   
} // namespace music
   
