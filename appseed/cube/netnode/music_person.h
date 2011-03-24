#pragma once

namespace music
{

   class CLASS_DECL_CA2_CUBE person :
      virtual public dso < person, ::dso_base >
   {
   public:
      /*var m_id;
      var m_name;
      var m_urlinfo;
      var m_urllist;
      var m_click;
      var m_songcount;
      var m_queryclassid;*/
      
      person();
      virtual ~person();
      
      virtual var get_html_link(var css_class);
      
   };

   

} // namespace music
