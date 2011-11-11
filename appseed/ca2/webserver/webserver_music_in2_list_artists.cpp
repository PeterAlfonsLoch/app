#include "StdAfx.h"

namespace webserver
{

namespace music
{
   
   in2_list_artists::in2_list_artists( var classid,  var namequerycode,  var order,  var target,  var query)
   {
      m_thislist = LISTID_CLASS_PERFORMER;
      m_thisnav = string(LISTID_CLASS_PERFORMER) + "," + gprop("param_nav");
      var nava;
      nava = explode(",", gprop("param_nav"));
      m_parentlist = nava.at(0);
      m_parentnav = gprop("param_nav").get_string().Mid(m_parentlist.get_string().get_length() + 1);
      m_classid = classid;
      m_classname = music().get_class_string(classid);
      dprint("classname: " + m_classname);
      m_namequerycode = namequerycode;
      m_performera = musicdb().get_performers(classid, namequerycode, order, target, query);
      m_dataa["classid"] = classid;
   }
   
   void in2_list_artists::print_js_include()
   {
   }
   
   string in2_list_artists::get_title()
   {
      /*global $param_locale;
      $db = &$this->db;
      $performer             = &$this->performer;
      $performername       = $performer->name;
      $classname            = $this->classname;
      return $db->getstring(20001)." - ".$this->classname." - ".music_getRootTitle($param_locale);*/
      return "";
   }
   
   void in2_list_artists::print_slist_preamble()
   {
      print("<div class='personlist3'>");
      print("<div class='personlist2'>");
      print("<div class='personlist1'>");
   
      print("<table width='100%' cellspacing='0' cellpadding='0'>");
      print("<tbody>");
      print("<tr>");
      print("<td valign='top' width='80%'>");
   }
   
   void in2_list_artists::print_slist_closure()
   {
      print("</td>");
      print("</tr>");
      print("</tbody>");
      print("</table>");
      print("</div>"); // personlist1
      print("</div>"); // personlist2
      print("</div>"); // personlist3
   }
   
   void in2_list_artists::print_list()
   {
      if(m_namequerycode.is_empty())
      {
         print(musicdb().get_string(20121));
      }
      else
      {
         gprop("code") = m_namequerycode;
         print(eval(musicdb().get_string(20122)));
      }
      performer_starttable();
      printrows();
      performer_endtable();
   }

   void in2_list_artists::printrows()
   {
      int line = 0;
      for(int i = 0; i < m_performera.array_get_count(); i++)
      {
         var performer = m_performera.at(i);
         print_row(performer.ca2 < ::webserver::music::performer >(), gprop("g_listline"));
         m_cur_line++;
         line++;
         gprop("g_listline")++;
      }
   }
   
   
   void in2_list_artists::print_row(::webserver::music::performer * pperformer, var line)
   {
//      int line = m_cur_line;
      
//      $r1path = "/sl.php";
      string r1path = "/";

      //$fwd_lang      = karaoke_getFwdParamLang();
      //$fwd_style   = karaoke_getFwdParamStyle();
      
      string thislist      = m_thislist;
      string parentlist    = m_parentlist;
      string thisnav       = m_thisnav;
      string parentnav     = m_parentnav;
      string performerid   = pperformer->m_id;
      string name          = pperformer->m_name;
      string songcount     = pperformer->m_songcount;
      string click         = pperformer->m_click;
      string queryclassid  = pperformer->m_queryclassid;
      string listname      = pperformer->get_list_name();
      
      string getclass;
      if(queryclassid == -1)
      {
         getclass = "";
      }
      else
      {
         getclass = "&class=" + queryclassid;
      }

      string mainlink = ui_url("songs?cid=" + queryclassid + "&aid=" + performerid + "&target=" + get("target"));
      
      print_tr(mainlink);

      print_td(-1);
//      echo "nav=".$nav;

//      print "<a class='item' href='$mainlink' title='$name'>";
      print("<a href='" + mainlink + "' title='" + name + "'>");
      print("<img class = 'i1i' src='i?p1n' title=\"\" alt=\"\" >\n");
      music().printListArtistSmallInclude(performerid);
      if(strlen(get("acode")) == 1 && get("acode") != "*" && get("acode") != "?")
      {
         print("<span class=\"acode-mark\">");
         print(listname.Mid(0, 1));
         print("</span>");
         print(listname.Mid(1));
      }
      else
      {
         print(listname);
      }
      print("</a>");
      print("</td>");


      print_td(-1);
      print("<img class = 'i1i' src='i?s1n' title=\"\" alt=\"\" >\n");
      print(songcount);
      print("</td>");

      print_td(-1);
      print(click);
      print("</td>");
      print("</tr>");
   }
   
} // namespace music


} // namespace webserver