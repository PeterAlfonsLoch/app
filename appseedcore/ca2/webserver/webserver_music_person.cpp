#include "StdAfx.h"


namespace webserver
{


   namespace music
   {

      person::person()
      {
      }

      person::~person()
      {
      }

      var person::get_html_link(var css_class)
      {
         string strCssClass(css_class);
         string a_cat;
         if(strCssClass.get_length() > 0)
         {
            a_cat = " class='" + strCssClass + "'";
         }
         string href = ui_url("songs?aid=" + m_propertyset["id"]);
         string link = "<a"+a_cat+" href='"+href+"'>";
         link += m_propertyset["name"];
         link += "</a>";
         return link;
      }


   } // namespace music


} // namespace webserver