#pragma once


namespace webserver
{

   namespace kar
   {

      class CLASS_DECL_ca page_artists :
         virtual public body_page
      {
      public:

         var m_perpertop;      
         var m_ppt_year;      
         var m_ppt_month;      
         var m_ppt_week;   
         music::in2_list_artists * m_plist;   
         AlphaSelectPerformer * m_pasp;   
         AlphaSelectLinkMaker * m_plm;   
         ui_nav * m_pnavYear;
         ui_nav * m_pnavSemester;
         ui_nav * m_pnavWeek;
         var m_title1;



         page_artists();

         /*function printHtmlTitle()
         {
         $this->printPageTitle();
         }

         function printPageTitle()
         {
         print $this->title1." - ".music_getRootTitle($param_locale);
         }*/


         virtual void print_head();

         virtual void print_body();


      };


   } // namespace kar


} // namespace webserver


