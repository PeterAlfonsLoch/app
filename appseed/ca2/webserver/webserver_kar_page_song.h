#pragma once


namespace webserver
{


   namespace kar
   {


      class CLASS_DECL_ca page_song :
         virtual public body_page
      {
      public:
         var m_perpertop;      
         var m_ppt_year;      
         var m_ppt_month;      
         var m_ppt_week;   
         music::in2_list_song * m_plist;   
         AlphaSelectPerformer * m_pasp;   
         AlphaSelectLinkMaker * m_plm;   
         ui_nav * m_pnavYear;
         ui_nav * m_pnavSemester;
         ui_nav * m_pnavMonth;
         ui_nav * m_pnavWeek;
         ui_nav_item * m_pcurNav;
         var m_title1;
         var m_pagetitle1;


         page_song();

         virtual void initialize_per_per_top(gen::property_set & params);

         virtual void print_head();

         virtual void print_body();


      };


   } // namespace kar


} // namespace webserver

