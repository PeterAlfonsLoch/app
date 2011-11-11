#include "stdafx.h"

namespace webserver
{

namespace kar
{

   page_artists::page_artists()
   {

      if(strlen(get("target")) > 0)
      {
         gprop("topictype") = get("target");
      }
      else
      {
         gprop("topictype") = gprop("g_music_topictype");
      }
         

      /*$params                   =  $_GET;
      $params['limitcount']    = $gtable['limitcount'];
         
      $param_querystyle = $_GET['slsttyp'];
      if(strlen($_GET['funuid']) > 0)
      {
         $param_querystyle = "fun";
      }*/
         
   //         $this->initializePerPerTop($params);
         
   //   print_r($params);
         
      m_plist = new music::in2_list_artists(get("cid"), get("acode"), get("order"), gprop("topictype"));

         
      AlphaSelectPerformerLinkMaker3 * plm = new AlphaSelectPerformerLinkMaker3();
      plm->m_strLang          = gprop("g_base_locale");
      plm->m_strStyle         = gprop("g_base_style");
      m_plm = plm;
         
      m_pasp                   = new AlphaSelectPerformer(get("target"));
      m_pasp->m_plinkmaker    = m_plm;
      /*m_pasp->js                = "_as";
      m_pasp->classid          = $_GET['cid'];
   
      $title1 = "";
      if($_GET['target'] == "chord")
      {
         $title1 = "{$langstr['Artists:Akkord']}: ";
      }
         
         
         
      if(strlen($this->list->classname) > 0)
      {
         if(strlen($this->list->namequerycode) > 0)
         {
            $title1 .= langstr('Artists:Sänger').": {$this->list->classname}: ".langstr('Artists:Filter').": ".$this->asp->code_getTitle($this->list->namequerycode);
         }
         else
         {
            $title1 .= langstr('Artists:Sänger').": {$this->list->classname}";
         }
      }
      else if(strlen($this->list->namequerycode) > 0)
      {
         $title1 .= langstr('Artists:Sänger').": ".langstr('Artists:Filter').": ".$this->asp->code_getTitle($this->list->namequerycode);
      }
      else
      {
         $title1 .= langstr('Artists:AlleSänger');
      }
         
      $this->title1 = $title1;*/
            
   }
   //////////////////////////////////////////////////////////////////////////
   //
   //  printHtmlTitle
   //
   //////////////////////////////////////////////////////////////////////////
      
   /*void page_artists::printHtmlTitle()
   {
      $this->printPageTitle();
   }

   void page_artists::printPageTitle()
   {
      print $this->title1." - ".music_getRootTitle($param_locale);
   }*/
      

   //////////////////////////////////////////////////////////////////////////
   //
   //  printHead
   //
   //////////////////////////////////////////////////////////////////////////
   
   void page_artists::print_head()
   {
      //veriwell_printcssinclude();
      m_plist->print_css_include();
      m_plist->print_js_include();
   
   }
   //////////////////////////////////////////////////////////////////////////
   //
   //  printBody
   //
   //////////////////////////////////////////////////////////////////////////
   
   void page_artists::print_body()
   {
      if(strlen(m_plist->m_classname) > 0)
      {
         music().printListClassInclude(m_plist->m_classid);
      }
      
      print("<span class=\"main-topic-level1\">");
      print(m_title1);
      print("</span>");

      m_pasp->out(3);
      print("<br>");
      m_plist->print_slist_preamble();
      m_plist->print_list();
      m_plist->print_slist_closure();


      print("<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
      print("<tr>");
      print("<td>&nbsp;</td>");
      print("<td>&nbsp;</td>");
      print("<td>&nbsp;</td>");
      print("</tr>");
      print("<tr>");
      print("<td align=\"left\" valign=\"top\">");
      menuleft_printVert001(music().menu_get_songs_menu(langstr("LeftMenu2:SearchSong:TopSongs") + ": " + langstr("LeftMenu2:SearchSong:TopSongs:7Day") ,"wt", get("cid"), get("aid")), 2);
      print("</td>");
      print("<td>&nbsp;</td>");
      print("<td align=\"left\" valign=\"top\">");
      menuleft_printVert001(music().menu_get_songs_menu(langstr("LeftMenu2:SearchSong:byTitle:LastInsertions") ,"li",  get("cid"), get("aid")), 2);
      print("</td>");
      print("</tr>");
      print("</table>");

   }

} // namespace kar


} // namespace webserver