#pragma once

namespace music
{
   
   class CLASS_DECL_CA2_CUBE performer :
      virtual public ptr
   {
   public:


      var m_id;
      var m_name;
      var m_urlinfo;
      var m_urllist;
      var m_click;
      var m_songcount;
      var m_queryclassid;
      var m_latinname;
      
      performer();
      virtual string get_html_link(const char  * css_class = "");
      virtual string get_list_name();

   };

   
   typedef ptr_array < performer > performer_ptr_array;

} // namespace music
