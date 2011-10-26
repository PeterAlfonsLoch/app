#include "StdAfx.h"

namespace webserver
{

namespace music
{

   in2_list::in2_list()
   {
      m_psonga = NULL;
      m_psonga2 = NULL;
   }


   in2_list::in2_list(var target, var order, var params_ex, gen::property_set params)
   {
      m_params.set_app(get_app());
      m_perf_perf_glue = " - ";
      m_perf_glue = ", ";
      m_bFirstPerf = true;
      m_bAsc = true;
      m_cur_line = 0;

      m_base_url_path = gprop("g_base_url");
      _set_params(params);
      if(!isset(gprop("g_listline")))
         gprop("g_listline") = 0;
      //m_imgsrca = gprop("listconfigimgscra");
      m_order = order;
      m_params_ex = params_ex;
      m_target = target;

      /*if(isset($params_ex[0]['params']))
      {
         if(isset($params_ex[0]['params'][2]))
         {
            m_formatstyle = $params_ex[0]['params'][2]['topic'];
         }
      }*/

   }

   string in2_list::get_list_title()
   {
      return m_listtitle;
   }

   void in2_list::print_css_include()
   {
      //global $param_style;
      //if(isset($param_style))
      {
//         print(" "<link rel='stylesheet' type='text/css' href='".veriwellList_getmaincsspath()."'>\n"");
//         print(" "<link rel='stylesheet' type='text/css' href='".veriwellList_getcsspath()."'>\n"");
      }
   }

   string in2_list::bold001( var text)
   {
      string textEx;
      textEx = "<span style=\"font-weight: bold;\">";
      textEx += text;
      textEx += "</span>";
      return textEx;
   }

   void in2_list::print_tr(var mainlink, var param)
   {

      if(!isset(gprop("g_listline")) || gprop("g_listline").is_empty())
         gprop("g_listline") = 0;
      var line = gprop("g_listline");
      m_tr_mdwn_parama.propset()[line] = mainlink;
      var thisid = m_id;
      var trid = "tr-" +thisid + "-" + line;
      var style;
      if(((int)line % 2) == 0)
      {
         style = "item0-tr";
      }
      else
      {
         style = "item1-tr";
      }
      //onmouseover    = "tr_movr(event, \""+thisid+"\", \""+line+"\")";
      //onmouseout    = "tr_mout(event, \""+thisid+"\", \""+line+"\")";
      //onmousedown    = "tr_mdwn(event, \""+thisid+"\", \""+line+"\", \""+param+"\")";
//      print(" "<tr id='$trid' class='$style' onmouseover='$onmouseover' onmouseout='$onmouseout' onmousedown='$onmousedown'>\n"");
      print(" <tr id='"+trid+"' class='"+style+"'>\n");
   }


   void in2_list::print_td(var i1, var prefix_style)
   {
      var style;
      if(((int)m_cur_line % 2) == 0)
      {
         style = "i0-td";
      }
      else
      {
         style = "i1-td";
      }
      style = prefix_style + style;
      print("<td class='"+style+"'>");
   }


      /* commented dec 2009


   void in2_list::performer_starttable()
   {
      // GET parameters

      // Sort
      //global $c_name;
      //global $c_click;

      var fwd_lang   = music().karaoke_getFwdParamLang();
      var fwd_style   = music().karaoke_getFwdParamStyle();

      gprop("list")          = m_list;

      gprop("style")       = m_style;

      gprop("order")       = m_order;

      print("<table border?\"0\" width=\"100%\" cellpadding=\"1\" cellspacing=\"1\" style=\"float:none;\">");
      print("<tbody>");
      print("<tr>");
      print("<td class=\"listheader1\">");
      if(gprop("order") != ORDERBY_PERFORMERNAME)
      {
         print("<a href='/artists?cid="+get("cid")+"&acode="+get("acode")+"&target="+get("target")+"&order="+ORDERBY_PERFORMERNAME+"'>");
      }
      print(" <img  class = 'i1ih' src='"+ music_imgsrc("performer.ico.16', 'normal") + "' title='' alt=''>\n");
      print_langstr("list.performer_header:Performer"); // Executante
      if($order != ORDERBY_PERFORMERNAME)
      {
         print(" </a>");
      }
      print(" </td>");

      print(" <td class=\"listheader1\">");
      print(" <img class = 'i1ih' src='" + music_imgsrc("song.ico.16', 'normal") + "' title='' alt=''>\n");
      print(langstr("list.performer_header:Songs")); // Msicas
      print(" </td>");

      print(" <td class=\"listheader1\">");
      if($order != ORDERBY_CLICK)
      {
         print(" <a href='/artists?cid={$_GET['cid']}&acode={$_GET['acode']}&target={$_GET['target']}&order=".ORDERBY_CLICK."'>");
      }
      print( langstr("list.performer_header:Hits")); // Cliques
      if($order != ORDERBY_CLICK)
      {
         print(" </a>");
      }
      print("</td>");

      print(" </tr>");

   }
   */

//   $titlea must be one item greater than linka
   void in2_list::print_out_nav(var linka, var titlea)
   {
      print("\r\n\
         <div class=\"divtopnavpeta\">\r\n\
         <div class=\"divtopnavtera\">\r\n\
         <div class=\"divtopnavnear\">\r\n\
         <div class=\"divtopnav\">\r\n\
      ");
      int count = linka.array_get_count();
      int i;
      for(i = 0; i < count; i++)
      {
         print(" <a href=\"" + linka[i] + "\" class=\"divtopnav-a\">"
             + titlea[i]+"</a>");
         print("  &gt; ");
      }
      print(" <span class=\"divtopnavsel-span\">"+ titlea[i] + "</span>");
      print("\r\n\
         </div>\r\n\
         </div>\r\n\
         </div>\r\n\
         </div>\r\n\
         \r\n\
         ");
   }

   /*
   void in2_list::performer_endtable()
   {
      print(" "</tbody>"");
      print(" "</table>"");
      m_tr_mdwn_parama_endtable();
   }*/

   void in2_list::tr_mdwn_parama_endtable()
   {
      music().js_tr_mdwn_parama(m_tr_mdwn_parama);
   }

   void in2_list::print_js_include()
   {
   }

   string in2_list::get_title()
   {
      return "";
   }

   void in2_list::print_navigation(var nav)
   {
//      global $param_nav;

      /*music().karaoke_print_navigation(
         m_thislist,
         gprop("param_nav"),
         m_dataa);*/
   }


   void in2_list::songa_print_kar_warning()
   {
   print("\r\n\
      <div class=\"karfilewarning-group2\">\r\n\
      <table width=\"100%\" cellpadding=\"0\" cellspacing=\"0\" class=\"karfilewarning-group1\">\r\n\
      <tbody><tr><td>\r\n\
      \r\n\
      ");

      var patha = get_kar_warning_path_list();

      System.lemon_array().randomize(patha.stra());

      for(int i = 0; i < patha.get_count(); i++)
      {
         print_kar_warning(patha[i]);
      }

      print("\r\n\
      </td>\r\n\
      </tr>\r\n\
      </tbody>\r\n\
      </table>\r\n\
      </div>\r\n\
      \r\n\
      ");
   }

   var in2_list::get_kar_warning_path_list()
   {
      var_array patha;
      var path = sys_get_include_path("ds", "partial", "kar_file_warning");

      if(strlen(path) > 0)
      {
         patha.add(path);
      }

      bool hasSpecificKaraoke = FALSE;

      for(int i = 0; i < m_psonga->get_count(); i++)
      {
        ::webserver:: music::song * psong = m_psonga->element_at(i);
         if(psong->calc_file_type() == "StarKorea3")
         {
            hasSpecificKaraoke = TRUE;
            break;
         }
         else if(psong->calc_file_type() == "Microke1")
         {
            hasSpecificKaraoke = TRUE;
            break;
         }
      }

      if(hasSpecificKaraoke)
      {
         path = sys_get_include_path("ds", "partial", "mk1_st3_song_warning");

         if(strlen(path) > 0)
         {
            patha.add(path);
         }
      }

      path = sys_get_include_path("ds", "partial", "song_err_warning");

      if(strlen(path) > 0)
      {
         patha.add(path);
      }
      return patha;
   }

   void in2_list::multi_page_init(int curpage, int limitcount)
   {
      if(curpage <= 0)
         m_curpage             = 1;
      else
         m_curpage             = curpage;
      m_limitcount       = limitcount;
   }

   void in2_list::multi_page_inst(int totalcount, int num_rows, int lastpage)
   {
      m_totalcount       = totalcount;
      m_num_rows         = num_rows;
      m_lastpage          = lastpage;
   }

   void in2_list::print_multi_page_nav(bool bInMulti)
   {
      if(m_totalcount <= m_limitcount)
         return;
      int previouspage     = m_curpage - 1;
      int nextpage         = m_curpage + 1;
//      int resultstart       = multi_page_get_result_start();
//      int resultend         = multi_page_get_result_end();
//      int limitcount       = m_limitcount;
      int num_rows         = m_num_rows;
      int lastpage         = m_lastpage;

      int curpage            = m_curpage;
      int listfirstpage    = multi_page_get_list_first_page();
      int listlastpage       = multi_page_get_list_last_page();


      var href;
      if(previouspage >= 1 && num_rows > 0)
      {
         href = multi_page_get_nav_link(previouspage);
         print(" <a class = 'results-access' href='"+href+"'>\n");
         print_langstr("song.list.results:previous"); //  "Previous Page"
         print("<span class = 'results-append'>\n");
         print(multi_page_get_nav_link_text_append(previouspage));
         print("</span>");
         print("</a>\n");
           print("    ");
      }
/*         else
      {
         print(" "<span class='results-access'>"");
               print(" langstr("song.list.results:previous")"); //  "Previous Page"
         print(" "<span class = 'results-append'>\n"");
         print(" multi_page_get_NavLinkTextAppend($previouspage)");
         print(" "</span>"");
         print(" "</span>"");
           print(" "    "");
      }*/

      if(bInMulti)
      {
         print("&nbsp;");
         for(int page = listfirstpage; page <= listlastpage; page++)
         {
            int userpage = page;
            int resnumber = (userpage - 1) * m_limitcount + 1;
            if(page == curpage)
            {
               print(" <span class='page-res-curitem'>$resnumber");
               print(" <span class = 'results-append'>\n");
               print(multi_page_get_nav_link_text_append(page));
               print(" </span>");
               print(" </span>"); // Curreent page
            }
            else
            {
               href = multi_page_get_nav_link(page);
               print(" <a class = 'page-res-item' href='"+href+"'>");
               print(gen::str::itoa(resnumber)); //  Other Pages quick access
               print("<span class = 'results-append'>\n");
               print(multi_page_get_nav_link_text_append(page));
               print("</span>");
               print("</a>\n");
            }
            print("&nbsp;");
         }
         print(" &nbsp;");
      }


      if(!lastpage)
      {
         href = multi_page_get_nav_link(nextpage);
         print(" <a class = 'results-access' href='"+href+"'>\n");
         print_langstr("song.list.results:next"); // "Next Page"
         print(" <span class = 'results-append'>\n");
         print(multi_page_get_nav_link_text_append(nextpage));
         print(" </span>");
         print(" </a>\n");
      }
/*      else
      {
         print(" "<span class='results-access'>"");
         print(" langstr("song.list.results:next")"); // "Next Page"
         print(" "<span class = 'results-append'>\n"");
         print(" multi_page_get_NavLinkTextAppend($nextpage)");
         print(" "</span>"");
         print(" "</span>"");
      }*/
/*      print(" "                 "");
      print(" "<span class='results-access'>"");
      print(" langstr("song.list.results:results")." {$resultstart} - {$resultend}"");
      print(" "</span>"");*/
      print(" <br>");
   }

   int in2_list::multi_page_get_list_first_page()
   {
      int curpage            = m_curpage;
      int listfirstpage    = max(1, curpage - 5);
      return listfirstpage;
   }
   int in2_list::multi_page_get_list_last_page()
   {
      int curpage            = m_curpage;
      int listlastpage       = min(curpage + 4, ((m_totalcount - 1) / m_limitcount) + 1);
      return listlastpage;
   }

   int in2_list::multi_page_get_limit_back_advance()
   {
      return max(0, multi_page_get_limit_start() - 5 * m_limitcount);
   }

   int in2_list::multi_page_get_limit_start()
   {
      return (m_curpage - 1) * m_limitcount;
   }

   int in2_list::multi_page_get_result_start()
   {
      return multi_page_get_limit_start() + 1;
   }

   int in2_list::multi_page_get_result_end()
   {
      return min(multi_page_get_limit_start() + m_limitcount, m_totalcount);
   }

   int in2_list::multi_page_get_limit_advance()
   {
      return min(multi_page_get_limit_start() + m_limitcount * 6, m_totalcount);
   }

   string in2_list::multi_page_get_nav_link(var page)
   {
      return m_call_url.get_string() + "?page=" + gen::str::itoa(page) + "&" + m_params.get_http_post();
   }

   void in2_list::print_slist_closure()
   {
   }

   var in2_list::get_accept_params()
   {
      return array();
   }

   void in2_list::_set_params(gen::property_set & params)
   {
      var accepta = get_accept_params();
      for(int i = 0; i < params.m_propertya.get_count(); i++)
      {
         if(accepta.stra().contains(params.m_propertya[i].name()))
         {
            m_params[params.m_propertya[i].name()] = params.m_propertya[i].get_value();
         }
      }
   }

   bool in2_list::has_param(var paramName)
   {
//      dprint("$paramName");
      if(m_params[paramName].is_set())
      {
      //   dprint(""-set]"");
         if(strlen(m_params[paramName]) > 0)
         {
            //dprint(""-goodlen}"");
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
   }

   string in2_list::multi_page_get_nav_link_text_append(var page)
   {
      return "";
   }

   int in2_list::multi_page_get_item_start()
   {
      return multi_page_map_to_internal_item(multi_page_get_limit_start());
   }

   int in2_list::multi_page_get_item_end()
   {
      return multi_page_map_to_internal_item(multi_page_get_result_end());
   }


   int in2_list::multi_page_map_to_internal_item(int item)
   {
      return item - ((multi_page_get_list_first_page() - 1) * m_limitcount);
   }


   // getTitle
   // printSListPreamble
   // printList
   // printSListClosure

   void in2_list::print_kar_warning(const char * path)
   {
   print("\r\n\
   <table cellpadding=\"0\" cellspacing=\"0\" width=\"100%\" class=\"kar-file-warning2\">\r\n\
   <tbody>\r\n\
   <tr>\r\n\
   <td>\r\n\
<div class=\"kar-file-warning1\">\r\n\
");

      include(path);
      print("\r\n\
      </div>\r\n\
      </td></tr></tbody>\r\n\
      \r\n\
      </table>\r\n\
   ");
   }


   void in2_list::performer_starttable()
	{
		// GET parameters

		// Sort
/*		global $c_name;
		global $c_click;

		$fwd_lang	= karaoke_getFwdParamLang();
		$fwd_style	= karaoke_getFwdParamStyle();*/


		//string list 		= m_list;
		//string style 		= m_style;
		string order 		= m_order;

		print("<table border?\"0\" width=\"100%\" cellpadding=\"1\" cellspacing=\"1\" style=\"float:none;\">");
		print("<tbody>");
		print("<tr>");
		print("<td class=\"listheader1\">");
		if(order != ORDERBY_PERFORMERNAME)
		{
			print("<a href='/artists?cid=" + get("cid") + "&acode=" + get("acode") + "&target=" + get("target") + "&order=" + ORDERBY_PERFORMERNAME + "'>");
		}
		print("<img  class = 'i1ih' src='" + music().imgsrc("performer.ico.16", "normal") + "' title='' alt=''>\n");
		print(langstr("list.performer_header:Performer")); // Executante
		if(order != ORDERBY_PERFORMERNAME)
		{
			print("</a>");
		}
		print("</td>");

		print("<td class=\"listheader1\">");
		print("<img class = 'i1ih' src='" + music().imgsrc("song.ico.16", "normal") + "' title='' alt=''>\n");
		print(langstr("list.performer_header:Songs")); // Msicas
		print("</td>");

		print("<td class=\"listheader1\">");
		if(order != ORDERBY_CLICK)
		{
			print("<a href='/artists?cid=" + get("cid") + "&acode=" + get("acode") + "&target=" + get("target") + "&order=" + ORDERBY_CLICK + "'>");
		}
		print(langstr("list.performer_header:Hits")); // Cliques
		if(order != ORDERBY_CLICK)
		{
			print("</a>");
		}
		print("</td>");
		print("</tr>");

	}


//	$titlea must be one item greater than linka
	/*function printOutNav($linka, $titlea)
	{
		?>
			<div class="divtopnavpeta">r
			<div class="divtopnavtera">
			<div class="divtopnavnear">
         <div class="divtopnav">
		<?php
		$count = count($linka);
		for($i = 0; $i < $count; $i++)
		{
			print "<a href=\"".$linka[$i]."\" class=\"divtopnav-a\">".$titlea[$i]."</a>";
			print " &gt; ";
		}
		print "<span class=\"divtopnavsel-span\">".$titlea[$i]."</span>";
		?>
			</div>
			</div>
			</div>
         </div>
		<?php
	}*/

	void in2_list::performer_endtable()
	{
		print("</tbody>");
		print("</table>");
		tr_mdwn_parama_endtable();
	}


} // namespace music

} // namespace webserver
