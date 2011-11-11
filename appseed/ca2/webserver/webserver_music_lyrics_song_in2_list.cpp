#include "StdAfx.h"


namespace webserver
{


namespace music
{


   lyrics_song_in2_list::lyrics_song_in2_list(var songid, var pgid, var topic, var topictype) :
      in2_info_list(songid, pgid, topic, topictype)
   {
   }

	string lyrics_song_in2_list::get_list_title()
	{
		return pstr("list:lyricssong:listtitle1");
	}
		
		
	void lyrics_song_in2_list::print_row(int iIndex, ::webserver::music::song * psong, int line)
	{
		//$selected = $this->is_selected($song, $lis);
		bool bSelected = false;
		var pgid = iIndex + 1;
      var lyricslink;
		if(isset(get("fwdaction")))
		{
			lyricslink = ui_url(get("fwdaction") +  "?topic="+psong->m_propertyset["topic"]+"&topictype="+psong->m_propertyset["topictype"]);
		}
		else
		{
			lyricslink = ui_url("song?sinfotyp=lyrics&sid="+psong->m_propertyset["id"]+"&pgid=" + pgid);
		}
			
		var mainlink = lyricslink;		
		print_tr(mainlink);
		//tr_mdwn_parama[$line] = $mainlink;
			
		print_td(-1);
		if(bSelected)
		{
			print("*");
		}
		else
		{
			print("&nbsp;");
		}
		print("</td>");
			
		print_td(-1);
		print("<strong>");
		print(gen::str::itoa(iIndex + 1));
		print("</strong>");
		print("</td>");
			
		print_td(-1);
		print(psong->m_propertyset["title"]);
		print("</td>");

		print_td(-1);
		if(strlen(psong->m_propertyset["lyricscomment"]) > 0 || psong->m_propertyset["translation_language"] >= 0)
		{
			print( psong->m_propertyset["lyricscomment"]);
			if(psong->m_propertyset["translation_language"] >= 0)
			{
				/*$langvalue['language'] = musicdb().get_language_name($song->translation_language);
				print ' - '.langstr2('list:lyricssong:comment:translationto');*/
			}
		}
		else
		{
			print( pstr("list:lyricssong:emptylyricscomment"));
		}
		print( "</td>");
			
		print_td(-1);
		// Lyrics
		string strTitle 	=  	pstr("list.song_printRow:Lyrics");
		string strAlt 	=  	pstr("list.song_printRow:Lyrics");
		print_td(16, "litd");
		if(!bSelected)
		{
			print( "<a href='" + lyricslink + "'>");
			print( "<img class=\"i1il\" src=\"/i?sl1n\" title=\"" + strTitle + "\" alt=\"" + strAlt + "\" id='lyricsImg." +gen::str::itoa(line)+"'>");
			print( "</a>");
		}
		else
		{
			print( "<img class=\"i1il\" src=\"/i?sl1d\"title=\"" + strTitle + "\" alt=\"" + strAlt + "\" id='lyricsImg." +gen::str::itoa(line)+"'>");
		}
		print("</td>\n");

		print( "</tr>");
			
	}
		
		
	
} // namespace music;


} // namespace webserver