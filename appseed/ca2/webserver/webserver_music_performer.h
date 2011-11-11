#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca performer :
         virtual public dynamic_source::ptr
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


      typedef dynamic_source::ptr_array < performer > performer_ptr_array;


   } // namespace music


} // namespace webserver


