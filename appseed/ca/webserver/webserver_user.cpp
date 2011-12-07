#include "StdAfx.h"


namespace webserver
{


ui_menu::~ui_menu()
{
}

ui_menu::ui_menu(
                 const char * pszTitle,
                 const char * pszLink,
                 const char * pszId)
{
   m_strTitle  = pszTitle;
   m_strLink   = pszLink;
   m_strId     = pszId;
}

ui_redir::ui_redir(::ca::application * papp) :
ca(papp)
{
}

void ui_redir::load_xml(const char * pszFileName)
{
   xml::node node(get_app());
   node.load(Application.file().as_string(pszFileName));
   for(int i = 0; i < node.get_children_count(); i++)
   {
      add(
         node.child_at(i)->attr("root"),
         node.child_at(i)->attr("lang"),
         node.child_at(i)->attr("style"),
         node.child_at(i)->attr("target"));
   }
}

void ui_redir::add(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszTarget)
{
   operator[](pszRoot)[pszStyle][pszLang].m_strTarget = pszTarget;
}
string ui_redir::solve(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszExUri)
{
   string strTarget = operator[](pszRoot)[pszStyle][pszLang].m_strTarget;
   if(strTarget.has_char())
      return strTarget + pszExUri;
   strTarget = operator[](pszRoot)[pszRoot][pszLang].m_strTarget;
   if(strTarget.has_char())
      return strTarget + pszExUri;
   strTarget = operator[](pszRoot)["_std"][pszLang].m_strTarget;
   if(strTarget.has_char())
      return strTarget + pszExUri;
   strTarget = operator[](pszRoot)[pszStyle]["_std"].m_strTarget;
   if(strTarget.has_char())
      return strTarget + pszExUri;
   strTarget = operator[](pszRoot)[pszRoot]["_std"].m_strTarget;
   if(strTarget.has_char())
      return strTarget + pszExUri;
   strTarget = operator[](pszRoot)["_std"]["_std"].m_strTarget;
   if(strTarget.has_char())
      return strTarget + pszExUri;
   return pszExUri;
}




   void user::veriwell_ws_print_menu(var name, var title, ui_menu * pmenu)
   {
      gprop("title") = title;
      gprop("name") = name;
      print("<div id=\"{$title}_menu\" style=\"z-index: 1; position: absolute; display: none; top: 0px; left: 0px;\">");
      print("<a href=\"javascript:showMenu('{$title}_menu', '', 'hide');\" class=\"menuclose1\">");
      print("<div style='float:left'>$label</div>");
      print("<div style='float:none;' align='right'>X</div>");
      print("</a>");
      print("\n");
      print("<div class=\"menu1\">");
      print("\n");
      print("\n");
      for(int i = 0; i < pmenu->get_count(); i++)
      {
         ui_menu & item = *pmenu->element_at(i);
         if(strlen(item.m_strTitle) == 0)
         {
            print("<span class=\"menuitem1\"></span>");
         }
         else
         {
            gprop("id") = "";
            if(strlen(item.m_strId) > 0)
            {
               gprop("id") = " id=\"{" + item.m_strId + "\" ";
            }
            print("<a href=\"" + item.m_strLink + "\" class=\"menuitem1\"{$id}>" + item.m_strTitle + "</a>");
         }
         print("\n");
      }
      print("</div>");
      print("\n");
      print("</div>");
      print("\n");
   }

   void user::veriwell_printOutNav1(var linka, var titlea)
   {
      print("\r\n\
            <div class=\"divtopnavpeta\">\r\n\
            <div class=\"divtopnavtera\">\r\n\
            <div class=\"divtopnavnear\">\r\n\
            <div class=\"divtopnav\">\r\n\
            \r\n\
            ");
      int count = linka.array_get_count();
      int i;
      for(i = 0; i < count; i++)
      {
         print("<a href=\"" + linka.at(i) + "\" class=\"divtopnav-a\">" + titlea.at(i) + "</a>");
         if(gprop("param_style") == "mb")
         {
            print(":&nbsp;");
         }
         else
         {
            print(" &gt; ");
         }
      }
      print("<span class=\"divtopnavsel-span\">" +  titlea.at(i) + "</span>");
      print("\r\n\
            </div>\r\n\
            </div>\r\n\
            </div>\r\n\
            </div>\r\n\
            \r\n\
            ");
   }

   void user::karaoke_printOutTabNav1(ui_nav * pnav)
   {
      print("\r\n\
            <table border=0 cellpadding=0 cellspacing=0 class=\"middlenav-table\">\r\n\
            <tr>\r\n\
            \r\n\
            ");
      int count = pnav->get_count();
      for(int i = 0; i < count; i++)
      {
         ui_nav_item & item = *pnav->element_at(i);
         if(item.m_bCurrent)
         {
            print("<td class=\"middlenav-curtab\" >" + item.m_strTitle + "</td>");
         }
         else if(item.m_bEnable)
         {
            print("<td class=\"middlenav-tab-sel\" ><a href=\"" + item.m_strLink + "\" class=\"middlenav-tab-a\">" + item.m_strTitle + "</a></td>");
         }
         else
         {
            print("<td class=\"middlenav-tab\" >" + item.m_strTitle +  "</td>");
         }
         print("<td width=20 class=\"middlenav-tabsp\" >&nbsp;</td>");
      }
      print("\r\n\
            <td class=\"middlenav-tabsp\">&nbsp;</td>\r\n\
            </tr>\r\n\
            </table>\r\n\
            ");
   }


   void user::karaoke_printOutTabNav5(ui_nav * pnav)
   {
      print("\r\n\
            <table border=0 cellpadding=0 cellspacing=0 class=\"middlenav-table\">\r\n\
            <tr>\r\n\
            \r\n\
            ");
      int count = pnav->get_count();
      for(int i = 0; i < count; i++)
      {
         ui_nav_item & item = *pnav->element_at(i);
         if(item.m_bCurrent)
         {
            print("<td class=\"middlenav-curtab\" >" + item.m_strTitle + "</td>");
         }
         else if(item.m_bEnable)
         {
            print("<td class=\"middlenav-tab\" ><a href=\"" + item.m_strLink + + "\" class=\"middlenav-tab-a\">" + item.m_strTitle + "</a></td>");
         }
         else
         {
            print("<td class=\"middlenav-tab\" >" + item.m_strTitle + "</td>");
         }
         print("<td width=20 class=\"middlenav-tabsp\" >&nbsp;</td>");
      }
      print("\r\n\
            <td class=\"middlenav-tabsp\">&nbsp;</td>\r\n\
            </tr>\r\n\
            </table>\r\n\
            ");
   }

   void user::karaoke_printOutTabNav2(ui_nav * pnav)
   {
      print("\r\n\
            <table border=0 cellpadding=0 cellspacing=0 class=\"middlenav-table\">\r\n\
            <tr>\r\n\
            \r\n\
            ");
      int count = pnav->get_count();
      for(int i = 0; i < count; i++)
      {
         ui_nav_item & item = *pnav->element_at(i);
         if(item.m_bCurrent)
         {
            print("<td class=\"middlenav-curtab\" >" + item.m_strTitle + "</td>");
         }
         else if(item.m_bEnable)
         {
            print("<td class=\"middlenav-tab-sel\" ><a href=\"" + item.m_strLink + "\" class=\"middlenav-tab-a\">" + item.m_strTitle + "</a></td>");
         }
         else
         {
            print("<td class=\"middlenav-tab\" >" + item.m_strTitle + "</td>");
         }
         if(i < count - 1)
         {
            print("<td width=20 class=\"middlenav-tabsp\" >&nbsp;</td>");
         }
      }
      print("\r\n\
            </tr>\r\n\
            </table>\r\n\
            \r\n\
            ");
   }

   void user::karaoke_printOutTabNav70(ui_nav * pnav)
   {
      int count = pnav->get_count();
      double percent_total_tab_sp = (count - 1) * 2;
      double percent_total_tab = 90 - percent_total_tab_sp;
      double percent_tab_sp = 100;
      if(count - 1 > 0)
      {
         percent_tab_sp = percent_total_tab_sp / (count - 1);
      }
      double percent_tab = percent_total_tab / count;
      print("\r\n\
            <table border=0 cellpadding=0 cellspacing=0 class=\"middlenav-table\" style=\"width:100%;\">\r\n\
            <tr>\r\n\
            \r\n\
            ");
      for(int i = 0; i < count; i++)
      {
         ui_nav_item & item = *pnav->element_at(i);
         if(item.m_bCurrent)
         {
            print("<td class=\"middlenav-curtab\" style=\"font-size: 80%; font-weight: normal; width: " + gen::str::itoa((int) percent_tab) + "%;\">" + item.m_strTitle + "</td>");
         }
         else if(item.m_bEnable)
         {
            print("<td class=\"middlenav-tab-sel\" style=\"font-size: 80%; font-weight: normal; width: " + gen::str::itoa((int) percent_tab) + "%;\"><a href=\"" + item.m_strLink + "\" class=\"middlenav-tab-a\">" + item.m_strTitle + "</a></td>");
         }
         else
         {
            print("<td class=\"middlenav-tab\" style=\"font-size: 80%; font-weight: normal;  width: <" + gen::str::itoa((int) percent_tab) + "%;\">" + item.m_strTitle + "</td>");
         }
         if(i < count  - 1)
         {
            print("<td width=20 class=\"middlenav-tabsp\" style=\"font-size: 80%; width: " + gen::str::itoa((int) percent_tab_sp) + "%;\">&nbsp;</td>");
         }
      }
      print("\r\n\
            </tr>\r\n\
            </table>\r\n\
            \r\n\
            ");
   }


} // namespace webserver
