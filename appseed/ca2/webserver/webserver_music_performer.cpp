#include "StdAfx.h"


namespace webserver
{


   namespace music
   {


      performer::performer()
      {
         m_queryclassid = -1;
      }

      string performer::get_html_link(const char * css_class)
      {
         string a_cat;
         if(strlen(css_class) > 0)
         {
            a_cat.Format(" class='%s'", css_class);
         }
         string performerid = m_id;
         string href = ui_url("songs?aid=" + performerid);
         string link;
         link = "<a" + a_cat + " href='" + href + "'>";
         link += m_name;
         link += "</a>";
         return link;
      }

      string performer::get_list_name()
      {
         if(strlen(m_latinname) > 0)
            return m_latinname;
         else
            return m_name;
      }


   } // namespace music


} // namespace webserver