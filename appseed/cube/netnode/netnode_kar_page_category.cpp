#include "StdAfx.h"

namespace kar
{
		
		
	page_category::page_category()
	{
      musicdb().m_getstring_languageid = 0;
      string topictype;			
		if(strlen(get("target")) > 0)
		{
			topictype = get("target");
		}
		else
		{
			topictype = gprop("g_music_topictype");
		}
/*      var params;
		params 						= geta();
		params["limitcount"] 	= $gtable['limitcount'];*/
			
		gprop("param_querystyle") = get("slsttyp");
		if(strlen(get("funuid")) > 0)
		{
			gprop("param_querystyle") = "fun";
		}
			
//			$this->initializePerPerTop($params);
			
	//	print_r($params);
			
		/*if(isset(gprop("request_params")))
		{
			$param_classid 		= $request_params_ex[4]['topic'];
			$param_performerid 	= $request_params_ex[5]['topic'];
			$param_songid 			= $request_params_ex[6]['topic'];
			$param_order 			= $request_params_ex[7]['topic'];
	//		print "param_classid=".$param_classid;
		}*/
			
		//require_once "site/karaoke/library/music/in2-list/category.ds";
		m_plist = new music::in2_list_category(get("order"), get("cid"), topictype);	
				
		if(m_plist->m_classa.array_get_count() <= 0)
		{
			//header("Location: {$this->base_url_path}artists?cid=" + get("cid") + "&target="+get("target"));
         header("Location: artists?cid=" + get("cid") + "&target="+get("target"));
			exit(0);
		}
			
		var & title1 		= m_title1;
		var & pagetitle1 	= m_pagetitle1;
			
				
		if(get("target") == "chord")
		{	
			title1 = langstr("SongList:Chords");
		}
		else
		{
			title1 = langstr("SongList:Songs");
		}
	
		if(strlen(get("cid")) > 0)
		{
			title1 += ": ";
			title1 += langstr("list.category.category");
			title1 += ": ";
			title1 += m_plist->m_classname;
		}
		else
		{
			title1 += ": ";
			title1 += langstr("list.category.all_categories");
		}
		pagetitle1 += title1 + " - " + music().get_root_short_title();
				
		m_pasp = NULL;
			
		m_plm 					= new AlphaSelectPerformerLinkMaker3();
		m_plm->m_strLang 		= gprop("param_locale");
		m_plm->m_strStyle		= gprop("param_style");
			
			
		m_pasp 					   = new AlphaSelectPerformer(get("target"));
		m_pasp->m_plinkmaker    = m_plm;
		//m_pasp->m_js 			   = "_as";
		m_pasp->m_strClassId    = get("cid");
	}

	
//////////////////////////////////////////////////////////////////////////
//
//  printHead
//
//////////////////////////////////////////////////////////////////////////
	
void page_category::print_head()
{
/*		veriwell_printcssinclude();
	$this->list->printCssInclude();
	$this->list->print_jsInclude();	*/
	
}
//////////////////////////////////////////////////////////////////////////
//
//  printBody
//
//////////////////////////////////////////////////////////////////////////
	
void page_category::print_body()
{
	if(strlen(m_plist->m_parentclassname) > 0)
	{
		music().printListClassInclude(m_plist->m_parentclass);
	}
		
   print("<pan class=\"main-topic-level1-simpleblock\">");
   print(m_title1);
   print("</span>\n");
   print("<span class=\"main-topic-level1-simpleblock\">");
   print("<a href=\"/artists?cid=" + gprop("param_parentclass") + "&target=" + get("target") + "\">");
   print(langstr("Artists:AlleSänger"));
   print("</a></span>\n");
   m_pasp->out(3);

   print("<table width=\"100%\"  border=\"0\" cellspacing=\"0\" cellpadding=\"0\">\n");
   print("<tr>\n");
   print("<td valign=\"top\"><span class=\"main-topic-level1\">\n");
//   print(m_title2);
	print("</span>");
   
   m_plist->print_slist_preamble();
   m_plist->print_list();
   m_plist->print_slist_closure();
   
   print("</td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td>\n");
   print("<table width=\"100%\"  border=\"0\" cellspacing=\"0\" cellpadding=\"0\">\n");
   print("<tr>\n");
   print("<td>&nbsp;</td>\n");
   print("<td>&nbsp;</td>\n");
   print("<td>&nbsp;</td>\n");
   print("</tr>\n");
   print("<tr>\n");
   print("<td align=\"left\" valign=\"top\">\n");
   menuleft_printVert001(music().menu_get_songs_menu(langstr("LeftMenu2:SearchSong:TopSongs") + ": " + langstr("LeftMenu2:SearchSong:TopSongs:7Day") ,"wt", get("cid"), get("aid"), get("target")), 2);
   print("</td>\n");
   print("<td>&nbsp;</td>\n");
   print("<td align=\"left\" valign=\"top\">\n");
   menuleft_printVert001(music().menu_get_songs_menu(langstr("LeftMenu2:SearchSong:byTitle:LastInsertions") ,"li", get("cid"), get("aid"), get("target")), 2);
   print("</td>\n");
   print("</tr>\n");
   print("</table>\n");
   print("</td>\n");
   print("</tr>\n");
   print("</table>\n");

}
	

} // namespace kar