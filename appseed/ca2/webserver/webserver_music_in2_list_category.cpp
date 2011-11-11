#include "StdAfx.h"

namespace webserver
{

/////////////////////////////////////////////////////////////
// 	class MusicListPerformerClass
//		Category Listing for Performer Music List
/////////////////////////////////////////////////////////////

namespace music
{

	in2_list_category::in2_list_category(var order, var parentclass, var target)
	{
		m_thislist = LISTID_PERFORMER_CLASS;
		m_thisnav = LISTID_PERFORMER_CLASS;
		if(!gprop("param_nav").is_empty())
		{
			m_thisnav += "," + gprop("param_nav");
		}
      var nava;
      nava = explode(",", gprop("param_nav"));
		m_parentlist = nava[0];
		m_parentnav = gprop("param_nav").get_string().Mid(strlen(m_parentlist) + 1);
		m_parentclass = parentclass;
		m_classname = music().get_class_string(parentclass);
		m_classa = musicdb().get_classes_for_performers(2, order, parentclass, target);
		if(strlen(parentclass) > 0)
		{
			::webserver::music::category * pcategory = musicdb().get_class_for_performers(1, order, parentclass);
			m_parentclassname = pcategory->m_name;
			m_pparentclass = pcategory;
			//$class->name = $class->name." - ".$db->getstring(20280); // Todos executantes nesta categoria
//			array_unshift(m_classa, $class);
		}
		
		//m_nav = LISTID_PERFORMER_CLASS;
		m_dataa["classid"] = parentclass;
	}
	
/*	function getTitle()
	{
		global $param_locale;
		$db = &m_db;
		return $db->getstring(20003)." - ".music_getRootTitle($param_locale);
	}
	
	function print_jsInclude()
	{
	}*/

	void in2_list_category::print_slist_preamble()
	{
		//var classid 	= m_classid;
		var classname 	= m_classname;

		if(strlen(classname) > 0)
		{
			print("<h1>");
			print(classname);
			print("</h1>\n");
		}
	}
	
	void in2_list_category::print_list()
	{
		m_cur_line = 0;
		start_table();
		print_rows();
		end_table();
		print("</tbody>");
	   print("</table>");
	}

	void in2_list_category::print_rows()
	{
		for(int i = 0; i < m_classa.array_get_count(); i++)
		{
			print_row(m_classa.at(i).ca2 < ::webserver::music::category >());
			print("\n");
			m_cur_line++;
			gprop("g_listline")++;
		}
	}
	
	void in2_list_category::start_table()
	{
		print("<table border=\"0\" width=\"100%\" cellpadding=\"1\" cellspacing=\"1\">\n");
		
		gprop("category") = m_classname;
		string link;
      string line_modifier;
		if(strlen(get("cid")) == 0)
		{
			print("<tr>");
			print("<td class=\"listheader1\">");
			print(langstr2("list.class_startTable:Categories")); // Categoria
			print("</td>");
			print("</tr>");
			print("\n");
			

			link = ui_url("artists");
			print_tr(link);
	  		print_td(-1);
			print("<a class=\"item" +  line_modifier +"\" href=\"" +link+ "\">");
			print(langstr2("list.class_startTable:AllArtists")); // Categoria
			print("</a>");
			print("</td>");
			print("</tr>");
			print("\n");
			
//			m_tr_mdwn_parama[m_cur_line] = $link;
			m_cur_line++;
			gprop("g_listline")++;
		}
		else
		{
			
			print("<tr>");
			print("<td class=\"listheader1\">");
			print(langstr2("list.class_startTable:SubCategories")); // Categoria
			print("</td>");
			print("</tr>");
			print("\n");
			
			link = ui_url("artists?cid={$_GET['cid']}");
			print_tr(link);
	  		print_td(-1);
			print("<a class=\"item" +  line_modifier +"\" href=\"" +link+ "\">");
			print(langstr2("list.class_startTable:AllArtistsInThisCategory")); // Categoria
			print("</a>");
			print("</td>");
			print("</tr>");
			print("\n");
			
//			m_tr_mdwn_parama[m_cur_line] = $link;
			m_cur_line++;
			gprop("g_listline")++;
		}
	}
	
	void in2_list_category::end_table()
	{
		tr_mdwn_parama_endtable();
	}
	
	void in2_list_category::print_row(::webserver::music::category * pcategory)
	{
		gprop("r1path") = "/";
		
		var line_modifier = m_cur_line % 2;
		
		//$fwd_lang		= karaoke_getFwdParamLang();
		//$fwd_style	= karaoke_getFwdParamStyle();
		
		var thislist		= m_thislist;
		var parentlist		= m_parentlist;
		var thisnav			= m_thisnav;
		var parentnav		= m_parentnav;
		var classid				= pcategory->m_id;
		var classnavid			= pcategory->m_navid;
		var name 				= pcategory->m_name;
		var performercount 	= pcategory->m_performercount;
		var songcount 			= pcategory->m_songcount;
//		$click 			= $performer->click;
		//$queryclassid	= $performer->queryclassid;
		string getclass;
		/*if(queryclassid == -1)
		{
			getclass = "";
		}
		else
		{
			getclass = "&class=" + queryclassid;
		}*/
		
		string mainlink = ui_url("category?cid=" +classnavid+"&target=" + get("target"));
		

		
//		if(isset($mainsubcatlink))
	//	{
		//	m_tr_mdwn_parama[$line] = $mainsubcatlink;
//		}
	//	else
		//{
//			m_tr_mdwn_parama[$line] = $mainlink;
	//	}
		
		/*if(isset(pcategory->childrenclass) && count(pcategory->childrenclass) > 0)
		{
			print_tr(mainsubcatlink);
		}
		else*/
		{
			print_tr(mainlink);
		}
  
      print_td(-1);
		print("<a class=\"item" + line_modifier + "\" href=\""+mainlink+"\">");

		print(name);
		print("</a>");
		print("</td>");
		print("</tr>");
	}
	

} // namespace music


} // namespace webserver