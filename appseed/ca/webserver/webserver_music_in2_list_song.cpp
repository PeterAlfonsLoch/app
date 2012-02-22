#include "StdAfx.h"

namespace webserver
{

namespace music
{



   in2_list_song::in2_list_song(
      var query,
      var song,
      var lyrics,
      var querystyle,
      var order,
      ::index curpage,
      ::count limitcount,
      var cid,
      var aid,
      var target,
      var funuid,
      gen::property_set & params,
      var call_url)
      :
   in2_list(target, order, gen::g_newconst, params)
   {
      m_pperformer = NULL;
      m_previous_artist = NULL;
      m_next_artist = NULL;

      m_limitcount = limitcount;
      m_call_url = call_url;

      m_partista = new ::webserver::music::performer_ptr_array;

      m_topictype = musicdb().calc_topic_type(target);

      m_cid = cid;
      m_aid = aid;

      /*if(isset(params_ex[0]['params']))
      {
      querystyle = $params_ex[0]['params'][0]['topic'];
      if(isset($params_ex[0]['params'][0]['params']))
      {
      $querystyle_params = $params_ex[0]['params'][0]['params'];
      }
      if(isset($params_ex[0]['params'][1]))
      {
      $order = $params_ex[0]['params'][1]['topic'];
      }
      if(isset($params_ex[0]['params'][3]))
      {
      $limitstart = $params_ex[0]['params'][3]['topic'];
      }
      }*/

      //      print(" "MusicListSong::QUERYSTYLE=$querystyle"");

      //dprint("limitcount=$limitcount");


      //m_list = $param_list;
      m_thislist = "song";
      m_thislist = "song";
      //m_nav = $param_nav;
      m_query = query;
      m_lyrics = lyrics;
      m_querystyle = querystyle;
      multi_page_init(curpage, limitcount);
      ::index lastpage;
      ::count totalcount;
      m_psonga = musicdb().get_songs(
         m_params_ex,
         query,
         song,
         lyrics,
         querystyle,
         order,
         multi_page_get_limit_back_advance(),
         limitcount * 11,
         lastpage,
         totalcount,
         cid,
         aid,
         target,
         funuid,
         params);

      /*if(strlen(aid) > 0)
      {
      m_artista = musicdb().getPeopleAroundId(
      $aid, $cid, $topictype);



      $iFind = -1;
      for($i = 0 ; $i < count(m_artista); $i++)
      {
      if(m_artista[$i]->id == m_aid)
      {
      $iFind = $i;
      break;
      }
      }
      dprint("iFind=$iFind");
      if($iFind >= 0)
      {
      m_previous_artist    = m_artista[$iFind - 1];
      m_next_artist    = m_artista[$iFind + 1];

      dprint_r(m_previous_artist)");
      dprint_r(m_next_artist)");
      }
      }*/

      /*
      if(m_hasParam("cid"))
      {
      $params2 = $params;
      unset($params2['cid']);
      m_songa2 =   &$db->getSongs(
      m_params_ex,
      $query,
      $song,
      $lyrics,
      $querystyle,
      $order,
      m_multiPageGetLimitStart(),
      $limitcount,
      $lastpage,
      $totalcount,
      "",
      $aid,
      $target,
      $funuid,
      $params2);
      m_classname = veriwell_getclassstring($cid);
      }
      if(m_hasParam("aid"))
      {
      m_performer       = &$db->db_read->getPerson($aid);
      m_performername    = &m_performer->name;
      }*/


      lastpage = curpage == gen::math::ceil_div(totalcount, limitcount);


      multi_page_inst(totalcount, m_psonga->get_count(), lastpage);

      var navtitle;

      if(querystyle == SQS_GLOBAL_TOP)
      {
         navtitle = pstr("LeftMenu2:SearchSong:Accesses:GlobalTop"); // Global Top
      }
      else if(querystyle == SQS_WEEK_TOP)
      {
         navtitle = pstr("LeftMenu2:SearchSong:Accesses:WeekTop"); // Week`s Top
      }
      else if(querystyle == SQS_24HOUR_TOP)
      {
         navtitle = pstr("LeftMenu2:SearchSong:Accesses:24HourTop"); // 24 hours Top
      }
      else if(querystyle == SQS_LAST_INSERTIONS)
      {
         navtitle = pstr("LeftMenu2:SearchSong:byTitle:LastInsertions"); // Last Insertions
      }
      else if(querystyle == SQS_LAST_ACCESSES)
      {
         navtitle = pstr("LeftMenu2:SearchSong:byTitle:LastAccesses"); // Last Insertions
      }
      else if(querystyle == SQS_PER_WEEK_TOP)
      {
         navtitle = pstr("LeftMenu2:SearchSong:TopSongs:perWeekTop"); // Last Insertions
      }
      else if(querystyle == SQS_PER_MONTH_TOP)
      {
         navtitle = pstr("LeftMenu2:SearchSong:TopSongs:perMonthTop"); // Last Insertions
      }
      else if(querystyle == SQS_PER_YEAR_TOP)
      {
         navtitle = pstr("LeftMenu2:SearchSong:TopSongs:perYearTop"); // Last Insertions
      }

      //      $navtitle = langstr("SongList:Songs"); // todos as msicas
      m_styletitle = navtitle;
      if(strlen(navtitle) == 0)
      {
         navtitle = pstr("SongList:Songs"); // todos as msicas
      }
      var title;
      title = navtitle;
      m_navtitle = navtitle;
      title += " - " + music().get_root_title();
      m_title = title;
      ::count songcount = m_psonga->get_count();
      m_songcount   = songcount;
      m_num_rows   = songcount;
      m_dataa["songnavtitle"] = navtitle;
      m_dataa["classid"] = cid;
      m_dataa["performerid"] = aid;
      if(m_pperformer != NULL)
      {
         m_dataa["performername"] = m_pperformer->m_name;
      }

   }

   void in2_list_song::print_js_include()
   {
      //global $prefixjs;
   }


   string in2_list_song::get_title()
   {
      return m_title;
   }


   void in2_list_song::print_slist_preamble()
   {
      print("<table celpadding=\"0\" cellspacing=\"0\" class=\"songlist3\">");
      print("<tbody>");
      print("<tr>");
      print("<td class=\"songlist3-td\">");

      print("<table celpadding=\"0\" cellspacing=\"0\" class=\"songlist2\">");
      print("<tbody>");
      print("<tr>");
      print("<td class=\"songlist2-td\">");

      print("<table celpadding=\"0\" cellspacing=\"0\" class=\"songlist1\">");
      print("<tbody>");
      print("<tr>");
      print("<td class=\"songlist1-td\">");

      if(m_querystyle == SQS_LAST_ACCESSES)
      {
         print("<script>\n");
         for(int i = 0; i < m_psonga->get_count(); i++)
         {
            ::webserver::music::song * psong = m_psonga->element_at(i);
            print("acctimea[$i] = \"" + psong->m_propertyset["accessdatetime"] + "\";\n");
         }
         print("</script>\n");
      }
      gen::property_set value(get_app());
      if(has_param("cid"))
      {
         ::webserver::music::song_ptr_array * psonga = m_psonga;
         ::count num_rows             = psonga->get_count();
         ::webserver::music::song_ptr_array * psonga2                = m_psonga2;
         ::count num_rows2             = psonga2->get_count();
         ::webserver::music::performer * pperformer             = m_pperformer;
         var performerid         = pperformer->m_id;
         var performername       = pperformer->m_name;
         var performermainurl    = pperformer->m_urllist;
         var performerurlinfo    = pperformer->m_urlinfo;
         var classid               = m_cid;
         var classname            = m_classname;

         print("<h1>" +  performername + " - " + classname + "</h1>");

         //print("("<p><font face=\"Arial\"><a href="".urldecode($p_backinfo)."">"");
         //print(" veriwell_getstring(20005)"); // pgina anterior
         //print(" "</a></font></p>"");*/

         print("<p class='bodytext'>");
         print("\n");
         value["performer"]    = bold001(performername);
         value["category"]    = bold001(classname);
         print(pstr("list.song.preamble.description1", value));
         print("\n");
         print("<br>");

         if(num_rows2 > num_rows)
         {
            print("\n");
            value["performer"]    = bold001(performername);
            print(pstr("list.song.preamble.description2", value));
            print("<br>");
            print("\n");
            print("<a href='/songs?aid=$performerid'>");
            print(pstr("list.song.preamble.description3"));
            print("</a>");
            print("\n");
         }
         print("</p>");

         // Performer Web Site URL Link Feature Facility
         print("<p class='bodytext'>");
         music().veriwellkaraoke_printperformerurlinfo(performerurlinfo);
         print("</p>");

         print("<p class='bodytext'>");
         value["count"]    = bold001(m_songcount);
         print(pstr("list."
            + music().karaoke_to_song_info_topictype(m_topictype)
            + ".preamble.description4:"
            + music().karaoke_nfy_count(m_totalcount),
            value)); // Foram encontradas tantas m+usicas
         print("</p>");

         print_multi_page_nav();
      }
      else
      {
         var query            = m_query;
         var lyrics            = m_lyrics;
         var querystyle         = m_querystyle;
         var order            = m_order;
         var formatstyle      = m_formatstyle;


         var classid          = m_cid;
         var classname          = m_classname;

         var thislist          = m_thislist;




         print("<span class=\"main-topic-level1\">");
         print(get_list_title());
         print("</span>");

         // Número de músicas encontradas
         print("<span class=\"bodytext\">");
         value["count"]    = bold001(gen::str::itoa(m_totalcount));
         print(pstr(
            "list." +
            music().karaoke_to_song_info_topictype(m_topictype) +
            ".preamble.description4:" +
            music().karaoke_nfy_count(m_totalcount), value)); // Foram encontradas tantas m+usicas
         print("</span>");
         print("<br>");


         var r1path = "/";



         print_multi_page_nav();
      }
      if(has_param("aid"))
      {
         print("<span class='bodytext'>");
         print(pstr("list.song.previous_artist"));
         print("<strong>");
         string link = ui_url("songs?aid=" + m_previous_artist->m_id + "&cid=" + m_cid);
         print("<a href='" + link + "'>");
         print("m_previous_artist->m_name");
         print("</a>");
         print("</strong>");
         print("&nbsp; | &nbsp;");
         print(pstr("list.song.next_artist"));
         print("<strong>");
         link = ui_url("songs?aid=" + m_next_artist->m_id + "&cid=" + m_cid);
         print("<a href='" + link + "'>");
         print("m_next_artist->m_name");
         print("</a>");
         print("</strong>");
         print("</span>");
         print("<br>");
         print("<br>");
      }
   }

   void in2_list_song::print_list()
   {
      //      m_song_starttable();
      song_printrows();
      //m_song_endtable();
      //      print(" "</tbody>"");
      //   print(" "</table>"");
   }

   void in2_list_song::song_starttable()
   {
      var aid;
      if(!get("aid").is_empty())
      {
         aid = get("aid");
      }


      var fwd_lang      = music().karaoke_getFwdParamLang();
      var fwd_style      = music().karaoke_getFwdParamStyle();

      var list          = m_thislist;
      var order          = m_order;
      var querystyle    = m_querystyle;
      var formatstyle    = m_formatstyle;
      if(formatstyle == "sc")
      {
         print("\r\n\
               ?>\r\n\
               \r\n\
               <style>\r\n\
               <!--\r\n\
               \r\n\
               .slsc\r\n\
               {\r\n\
               text-align: center;\r\n\
               }\r\n\
               \r\n\
               -->\r\n\
               </style>\r\n\
               \r\n");
      }


      print("<table border=\"0\" cellpadding=\"1\" cellspacing=\"1\" class=\"list1\">");
      print("<tbody>");


      if(formatstyle == "sc")
         return;

      print("<tr>");
      if(m_bAsc)
      {
         print("<td class=\"listheader1\">");
         print(pstr("song-list-ranking")); // Executante
         print("</td>\n");
      }
      if(!has_param("aid"))
      {
         print("<td class=\"listheader1\">");
         //   print(" "<img class='i1ih' src='image/".$img_performer.ico.16."' title=\"\" alt=\"\">"");
         print(pstr("list.song_startTable:Performer")); // Executante
         print("</td>\n");
      }

      print("<td class=\"listheader1\">");
      if(order != ORDERBY_SONGNAME)
      {
         print("<a href='"+ ui_url("songs?slsttyp=" + m_querystyle + "&aid=" + m_aid + "&cid=" + m_cid + "&order=" +ORDERBY_CLICK+ "") +"'>");
      }
      //   print(" "<img class='i1ih' src='image/".$img_song.ico.16."' title=\"\" alt=\"\" >\n"");
      // Ttulo
      print(pstr("list.song_startTable:Title"));
      if(order != ORDERBY_SONGNAME)
      {
         print("</a>");
      }
      print("</td>");

      if(gprop("param_root") != "letras" & gprop("param_root") != "cifras")
      {
         // Tipo
         print("<td class=\"listheader1\">");
         print(pstr("list.song_startTable:Type"));
         print("</td>");
      }

      // Salvar/Fazer download
      var title = pstr("list.song_printRow:Save/Download");
      var alt    =  pstr("list.song_printRow:Save/Download");
      print("<td class=\"lhitd listheader1\">");
      print("<img src=\"" + simage("sd1n") + "\" title=\""+title+"\" alt=\""+alt+"\" >");
      print("</td>");

      // open/Play
      title    = pstr("list.song_printRow:open/Play");
      alt      = pstr("list.song_printRow:open/Play");
      print("<td class=\"lhitd listheader1\">");
      print("<img src=\"" + simage("sp1n") + "\" title=\""+title+"\" alt=\""+alt+"\" >");
      print("</td>");

      // Lyrics
      title    = pstr("list.song_printRow:Lyrics");
      alt       = pstr("list.song_printRow:Lyrics");
      print("<td class=\"lhitd listheader1\">");
      print("<img src=\"" + simage("sl1n") + "\" title=\""+title+"\" alt=\""+alt+"\" >");
      print("</td>");

      // Cifras
      title    = pstr("list.song_printRow:Chords");
      alt      = pstr("list.song_printRow:Chords");
      print("<td class=\"lhitd listheader1\">");
      print("<img src=\"" + simage("sc1n") + "\" title=\""+title+"\" alt=\""+alt+"\" >");
      print("</td>");


      // info
      title    = pstr("list.song_printRow:Details");
      alt      = pstr("list.song_printRow:Details");
      print("<td class=\"lhitd listheader1\">");
      print("<img src='" + simage("si1n") + "' title=\""+title+"\" alt=\""+alt+"\" >");
      print("</td>");

      // error
      title    = pstr("list.song_printRow:Report");
      alt      = pstr("list.song_printRow:Report");
      print("<td class=\"lhitd listheader1\">");
      print("<img src='" + simage("se1n") + "' title=\""+title+"\" alt=\""+alt+"\" >");
      print("</td>");

      // Fun!
      bool bFun = fun().is_active();
      if(bFun)
      {
         title    = pstr("list.song_printRow:Fun");
         alt      = pstr("list.song_printRow:Fun");
         print("<td class=\"lhitd listheader1\">");
         print("<img src='" + simage("f1n") + "' title=\""+title+"\" alt=\""+alt+"\" >");
         print("</td>");
      }
      print("<td class=\"listheader1\">");
      if(order != ORDERBY_GLOBALCLICK)
      {
         print("<a href='" + ui_url("songs?slsttyp=" + m_querystyle + "&aid=" + m_aid + "&cid=" + m_cid + "&order=" + ORDERBY_GLOBALCLICK) + "'>");
      }
      print(pstr("list.song_startTable:Hits")); // Cliques
      if(order != ORDERBY_GLOBALCLICK)
      {
         print("</a>");
      }
      print("</td>");

      if(m_querystyle == SQS_LAST_ACCESSES)
      {
         title    = pstr("SongListHeader:AccessDateTime");
         alt      = pstr("SongListHeader:AccessDateTime");
         print("<td class=\"listheader1\">");
         print("<img src='" + simage("sadt1n") + "' title=\"" + title + "\" alt=\"" + alt + "\">");
         print("</td>");

         /*         $title    = langstr("SongListHeader:AccessSource");
         $alt       = langstr("SongListHeader:AccessSource");
         print(" "<td class=\"listheader1\">"");
         print(" "<img src='i?sadt1n' title=\"$title\" alt=\"$alt\">"");
         print(" "</td>"");*/
      }

      print("</tr>");

   }

   void in2_list_song::printrows()
   {
      ::index pos = 0;
      for(::index i = multi_page_get_limit_start();
         i < multi_page_get_limit_start() + m_limitcount;
         i++)
      {
         print_row(m_psonga->element_at(i), gprop("g_listline").get_integer());
         m_cur_line++;
         gprop("g_listline")++;
         pos++;
      }
      //      song_printrows();
   }


   void in2_list_song::song_printrows()
   {
//      int pos = 0;
      stringa performerlinka;
      stringa performeridsa;

      var_array performerlinkaa;
      stringa titlea;
      string performerid;
      string title1;
      string href;
      stringa other_performers;
      string link;
      var_array performerurlinfoa;
      var_array performerurlinfoaa;
      stringa performerida;

      //dprint("yyy(".$_GET['aid'].")");
      if(has_param("aid"))
      {
         //dprint("xxx(".$_GET['aid'].")");
         for(::index i = multi_page_get_item_start();
            i < multi_page_get_item_end();
            i++)
         {
            ::webserver::music::song * psong = m_psonga->element_at(i);
            if(performeridsa.add_unique_ci(psong->m_propertyset["performerids"]))
            {
               performerlinka.remove_all();
               performerurlinfoa.remove_all();
               other_performers.remove_all();
               for(int j = 0; j < psong->m_propertyset["pperformera"].array_get_count(); j++)
               {
                  ::webserver::music::person * pperformer = psong->m_propertyset["pperformera"].at(j).ca2 < ::webserver::music::person >();
                  performerid = pperformer->m_propertyset["id"];
                  //            print(" "pid($performerid)"");
                  if(performerid == get("aid"))
                  {
                     title1 = pperformer->m_propertyset["name"];
                  }
                  else
                  {
                     other_performers.add((const char *) pperformer->m_propertyset["name"]);
                  }
                  href = "/songs?aid=$performerid";
                  link = "<a class='listtitleperf-a' href='" + href + "'>";
                  link += pperformer->m_propertyset["name"];
                  link += "</a>";
                  performerlinka.add(link);
                  //                  print(" "urlinof"");
                  //               print_r($performer->urlinfo)");
                  performerurlinfoa.add(pperformer->m_propertyset["urlinfo"]);
                  performerida.add(performerid);
               }
               //               print(" "title1=$title1"");
               performerlinkaa.add((var) performerlinka);
               performerurlinfoaa.add((var) performerurlinfoa);
               if(other_performers.get_count() > 0)
               {
                  if(!m_bFirstPerf)
                  {
                     title1 = "";
                  }
                  if(other_performers.get_count() > 1 && m_perf_perf_last_glue.is_set())
                  {
                     titlea.add(title1 + m_perf_perf_glue + other_performers.implode(m_perf_glue, (index) 0, -2) + m_perf_perf_last_glue + other_performers.last_element());
                  }
                  else
                  {
                     titlea.add(title1 + m_perf_perf_glue + other_performers.implode((const char *) m_perf_glue));
                  }
               }
               else
               {
                  titlea.add(title1);
               }

            }
         }
         //         print_r($performerurlinfoaa)");

         var performerids;

         for(int aakey = 0; aakey < performeridsa.get_count(); aakey++)
         {
            performerids = performeridsa[aakey];
            print("<span class='main-topic-level1'>");
            print("titlea[aakey]");
            print("</span>");
            print("<span class='listtitleperf-aset'>");
            print(performerlinkaa[aakey].stra().implode(", "));
            print("</span>");
            //      print(" "<br>"");
            // Performer Web Site URL Link Feature Facility
            song_starttable();
            for(::index i = multi_page_get_item_start();
               i < multi_page_get_item_end();
               i++)
            {
               ::webserver::music::song * psong = m_psonga->element_at(i);
               if(psong->m_propertyset["performerids"] == performerids)
               {
                  print_row(psong, gprop("g_listline"));
                  m_cur_line++;
                  gprop("g_listline")++;
               }
            }
            song_endtable();

            print("</table>");
            print("<p>");
            for(int j = 0; j < performerurlinfoaa[aakey].get_count(); j++)
            {
               music().veriwellkaraoke_printperformerurlinfo(performerurlinfoaa[aakey][j]);
            }
            print("</p>");
            print("<br>");
         }
      }
      else
      {
         song_starttable();
         for(::index i = multi_page_get_item_start();
            i < multi_page_get_item_end();
            i++)
         {
            ::webserver::music::song * psong = m_psonga->element_at(i);
            print_row(psong, gprop("g_listline"));
            m_cur_line++;
            gprop("g_listline")++;
         }
         song_endtable();
         print("</table>");
         print("<br>");

      }
   }



   void in2_list_song::print_row(::webserver::music::song * psong, index line)
   {
      /*      global $g_languageid;
      global $param_nav;
      global $basekaraokescripturl;
      global $secureuserid;
      global $karfilephppath;
      global $musicdb;
      global $langstr;
      global gprop("param_root");
      global $g_listline;*/

      var g_listline;
      var param_root;
      var zi;
      var r1path;
      var r2path;
      var refr;
      var hrefrefr;
      var fwd_lang;
      var fwd_style;
      var imgsrca;
      var thislist;
      var parentlist;
      var thisnav;
      var songid;
      var parentnav;
      var topic;
      var performers;
      //var performera;
      var filename;
      var title;
      var click;
      var type;
      var rank;
      var topictype;
      var formatstyle;
      var performerslink;
      var r3path;
      var itemnav;
      var performeridlist;
      var classidlist;


      zi = ui_url("i");

      //      $r1path = "/sl.php";

      r1path = "/";
      //      $r2path = "/i.php";

      r2path = "/";
      //      $r3path = "/file.php";
      r3path = "/";

      refr = music().sparam_url_encode(inattr("request_uri"));
      hrefrefr = urlencode(refr);

      fwd_lang          = music().karaoke_getFwdParamLang();
      fwd_style         = music().karaoke_getFwdParamStyle();

      //imgsrca           = m_imgsrca;

      thislist          = m_thislist;
      parentlist        = m_parentlist;
      thisnav           = m_thisnav;
      parentnav         = m_parentnav;
      songid            = psong->m_propertyset["id"];
      topic             = psong->m_propertyset["topic"];
      performers        = psong->m_propertyset["performers"];
      //performera        = psong->m_propertyset["performera;
      filename          = psong->m_propertyset["filename"];
      title             = psong->m_propertyset["title"];
      click             = psong->m_propertyset["click"];
      type              = psong->m_propertyset["type"];
      //bChords           = psong->m_propertyset["bChords;
      rank              = psong->m_propertyset["rank"];
      topictype         = psong->m_propertyset["topictype"];

      formatstyle       = m_formatstyle;

      var performerlinka = psong->get_performera_html_link("");
      performerslink     = psong->get_performera_html_link1("");

      itemnav = m_thislist;
      if(gprop("param_nav").is_set())
      {
         itemnav += "," + gprop("param_nav");
      }

      performeridlist = psong->get_performer_id_list();
      classidlist = m_cid;

      /*if(!m_performerid.is_empty())
      {
         performerid = m_performerid;
      }
      else
      {
         performerid = performeridlist;
      }*/

      var aid = get("aid");

      var classid;
      if(m_cid.is_set())
      {
         classid = m_cid;
      }
      else
      {
         classid = classidlist;
      }

      var infolink;
      var karaokelink;
      var chordlink;
      var lyricslink;
      var savelink;
      infolink       = ui_url("song?sinfotyp=general&sid=" + songid);
      karaokelink    = ui_url("song?sinfotyp=karaoke&sid=" + songid);
      chordlink       = ui_url("song?sinfotyp=chords&sid=" + songid);
      lyricslink       = ui_url("song?sinfotyp=lyrics&sid=" + songid);
      //      $savelink = ui_url("download?filename='.psong->filename.'&referer='.urlencode($_SERVER['REQUEST_URI']));
      savelink       = ui_url("/file/download/" + psong->m_propertyset["filename"]);
      if(m_target == "chord" || gprop("param_root") == "cifras")
      {
         karaokelink    = ui_url("song?sinfotyp=karaoke&topic="+ topic+"&topictype="+topictype);
      }
      else if(m_target == "letras" || gprop("param_root") == "letras")
      {
         karaokelink    = ui_url("song?sinfotyp=karaoke&topic="+topic+"&topictype="+topictype);
      }
      else
      {
         karaokelink    = ui_url("song?sinfotyp=karaoke&topic="+topic+"&topictype="+topictype);
      }

      var mainlink;
      if(m_target == "chord" || gprop("param_root") == "cifras")
      {
         mainlink = chordlink;
      }
      else if(m_target == "letras" || gprop("param_root") == "letras")
      {
         mainlink = lyricslink;
      }
      else
      {
         mainlink = karaokelink;
      }

      print_tr(mainlink);

      if(formatstyle == "sc")
      {
         print("_td(-1)");
         print( "<div class=\"slsc\">");
         print(performerlinka.implode(", "));
         print(" - ");
         print("<a href='"+ mainlink +"'>");
         if(title.is_empty())
         {
            print(filename);
         }
         else
         {
            print(title);
         }
         print("</a>");
         print("</div>");
         print("</td>");
         print("</tr>\n");
         return;
      }

      if(m_bAsc)
      {
         print_td(-1);
         if(rank > 0)
            print(rank);
         else
            print(gen::str::itoa(m_cur_line + m_limitcount * (m_curpage - 1) + 1));
         print("</td>\n");
      }

      // Save Cell
      if(!has_param("aid"))
      {
         print_td(-1);
         print(performerslink);
         print("</td>\n");
      }

      print_td(-1);
      //      print(" "<img  class='i1i' src='image/".$img_song.ico.16."' title=\"\" alt=\"\" >\n"");
      if(title.is_empty())
      {
         print(filename);
      }
      else
      {
         print(title);
      }
      print("</td>\n");

      if(gprop("param_root") != "letras" && gprop("param_root") != "cifras")
      {
         print_td(-1, "litd");
         print("<img src=\"" + music().song_get_song_type_image1(type) + "\">");
         print("</td>\n");
      }


      var link;
      // Download/Save Cell
      print_td(16, "litd");
      if(gprop("param_root") == "letras" || gprop("param_root") == "cifras")
      {
         link    =  karaokelink;
      }
      else
      {
         link    =    savelink;
      }
      var alt;
      title    =     langstr("list.song_printRow:Save/Download");
      alt    =     langstr("list.song_printRow:Save/Download");
      print(" <a href='"+link+"' >");
      print(" <img class=\"i1il\" src=\"" + simage("sd1n") + "\" title=\"$title\" alt=\"$alt\" id=\"saveImg.$line\">");
      print(title);
      print("</a>");
      print("</td>\n");

      // open Cell

      print_td(16, "litd");
      //      $link = $r3path."file/open/$filename";
      string strLinkTarget;
      if(gprop("param_root") == "letras" || gprop("param_root") == "cifras")
      {
         link    =    karaokelink;
         strLinkTarget = "";
      }
      else
      {
         //link    =    "javascript:open_kar_file('" + urlencode("file/open/" +filename+"") + "')";
         link  = "http://" + System.url().get_server(this_url()) + "/file/open/" +filename;
         strLinkTarget = " target=\"veriwell_musical_player\" ";
      }
      title    =  langstr("list.song_printRow:open/Play");
      alt    =     langstr("list.song_printRow:open/Play");
      print("<a href=\""+link+"\"" + strLinkTarget +">");
      print("<img class=\"i1il\" src=\"" + simage("sp1n") + "\" title=\"$title\" alt=\"$alt\" id=\"openImg.$line\">");
      print(title);
      print("</a>");
      print("</td>\n");

      // Lyrics
      title    =  langstr("list.song_printRow:Lyrics");
      alt    =     langstr("list.song_printRow:Lyrics");
      print_td(16, "litd");
      if(psong->m_propertyset["lyricscount"].get_integer() > 0)
      {
         print(" <a href='" +  lyricslink + "'>");
         print(" <img class=\"i1il\" src=\"" + simage("sl1n") + "\" title=\"$title\" alt=\"$alt\" id='lyricsImg.$line'>");
         print(title);
         print(" </a>");
      }
      else
      {
         print(" <img class=\"i1il\" src=\"" + simage("sl1d") + "\" title=\"$title\" alt=\"$alt\" id='lyricsImg.$line'>");
         print(title);
      }
      print(" </td>\n");

      // Cifras
      title    =     langstr("list.song_printRow:Chords");
      alt    =     langstr("list.song_printRow:Chords");
      bool bChords = psong->m_propertyset["chordcount"] > 0;
      print_td(16, "litd");
      var href;
      if(bChords)
      {
         href = chordlink;
         print(" <a href='"+href +"' >");
         print(" <img class=\"i1il\" src=\"" + simage("sc1n") + "\" title=\"$title\" alt=\"$alt\" id=\"chordImg.$line\">");
         print(title);
         print(" </a>");
      }
      else
      {
         print(" <img class=\"i1il\" src=\"" + simage("sc1d") + "\" title=\"$title\" alt=\"$alt\" id=\"chordImg.$line\">");
         print(title);
      }
      print(" </td>\n");


      // Information
      title    =     langstr("list.song_printRow:Details");
      alt    =     langstr("list.song_printRow:Details");
      print_td(16, "litd");
      print(" <a href='" + infolink + "' >");
      print(" <img class='i1il'src='" + simage("si1n") + "' title=\"$title\" alt=\"$alt\" id='infoImg.$line'>");
      print(title);
      print(" </a>");
      print(" </td>\n");

      // Exception
      title    =     langstr("list.song_printRow:Report");
      alt    =     langstr("list.song_printRow:Report");
      print_td(16, "litd");
      link = ui_url("song-err?songid=" + songid);
      print(" <a href='" + link + "'>");
      print(" <img class='i1il' src='" + simage("se1n") + "' title=\"$title\" alt=\"$alt\"   id='songExc.$line'>");
      print(title);
      print(" </a>");
      print(" </td>\n");


         bool bFun = fun().is_active();
      // Fun!
      if(bFun)
      {
         if(psong->m_propertyset["isfun"])
         {
            print_td(16, "litd");
            print("<a href='/fun?ToggleFun&song="+songid+"&ruri=" + urlencode(inattr("REQUEST_URI")) + "' ");
            //               print(" "onMouseDown=\"img_MouseDown("funImg', '$line")\""");
            //               print(" "onMouseOut=\"img_MouseOut("funImg', '$line")\""");
            //               print(" "onMouseOver=\"img_MouseOver("funImg', '$line")\""");
            //               print(" "onMouseUp=\"img_MouseUp("funImg', '$line")\""");
            print(" >");
            print("<img class='i1il'\r\n\
                  name='funImg." + gen::str::itoa(line) + "'\r\n\
                  src='" + simage("f1n") + "' title=\"\"\r\n\
                  alt=\"Fun\"\r\n\
                  id='funImg.$line'\r\n\
                  >\n");
            print("</a>");
            print("</td>\n");
         }
         else
         {
            print_td(16, "litd");
            print("<a href='/fun?ToggleFun&song="+songid+"&ruri="+urlencode(inattr("REQUEST_URI"))+"' ");
            //               print(" "onMouseDown=\"img_MouseDown("funNotImg', '$line")\""");
            //         print(" "onMouseOut=\"img_MouseOut("funNotImg', '$line")\""");
            //print(" "onMouseOver=\"img_MouseOver("funNotImg', '$line")\""");
            //               print(" "onMouseUp=\"img_MouseUp("funNotImg', '$line")\""");
            print(" >");
            print(" <img class='i1il' ");
            //                     name='funNotImg.$line'
            print(" src='" + simage("f1u") + "' title=\"\" \r\n\
               alt=\"(not fun)\"\r\n\
               id='funNotImg.$line'\r\n\
         >\n");
         print(" </a>");
            print("</td>\n");
         }
      }

      print_td(-1);
      print(click);
      print(" </td>");


      if(m_querystyle == SQS_LAST_ACCESSES)
      {
         print_td(-1);
         print(string(" <div id='acctime-")+line+"'>&nbsp;</div>");
         //         print(" psong->accessdatetime");
         //         print(" "&nbsp;"");
         print(" </td>");

         /*         m_print("_td($line, -1)");
         print(" psong->accesslang");
         print(" "</td>"");*/
      }


      // End Row
      print(" </tr>");
      print(" \n");

   }

   void in2_list_song::song_endtable()
   {
      //      m_tr_mdwn_parama_endtable();
   }



   void in2_list_song::print_slist_closure()
   {
      tr_mdwn_parama_endtable();

      print_multi_page_nav(TRUE);

      print("</td>");
      print( "</tr>");
      print( "</tbody>");
      print( "</table>"); // songlist1

      print( "</td>");
      print( "</tr>");
      print( "</tbody>");
      print( "</table>"); // songlist2

      print("</td>");
      print("</tr>");
      print("</tbody>");
      print("</table>"); // songlist3

      if(gprop("g_nosong_extra") != 1 && m_topictype == 0)
      {
         songa_print_kar_warning();
      }
   }


   var in2_list_song::get_accept_params()
   {
      var a;
      a.stra().add("target");
      a.stra().add("cid");
      a.stra().add("aid");
      a.stra().add("slsttyp");
      a.stra().add("year");
      a.stra().add("month");
      a.stra().add("week");
      a.stra().add("querymod");
      a.stra().add("querytyp");
      a.stra().add("querytxt");
      return a;
   }

   string in2_list_song::multi_page_get_nav_link_text_append(var page)
   {
      if((strlen(m_querystyle) == 0 || m_querystyle == "sls")
         && (strlen(m_order) == 0 || m_order == ORDERBY_SONGNAME))
      {
         page = page - 1;
         return "&nbsp;("+ string(m_psonga->element_at(multi_page_map_to_internal_item(page * (int) m_limitcount))->m_propertyset["title"]) +")";
      }
      else
      {
         return "";
      }
   }

} // namespace music


} // namespace webserver
