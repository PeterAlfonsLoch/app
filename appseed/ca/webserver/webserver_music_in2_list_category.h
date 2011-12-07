#pragma once


namespace webserver
{

   /////////////////////////////////////////////////////////////
   // 	class MusicListPerformerClass
   //		Category Listing for Performer Music List
   /////////////////////////////////////////////////////////////


   namespace music
   {

      class CLASS_DECL_ca in2_list_category :
         public in2_list
      {
      public:
         var m_classa;
         var m_parentclass;
         var m_parentclassname;
         webserver::music::category * m_pparentclass;
         var m_classname;

         in2_list_category(var order, var parentclass, var target = "");

         /*function getTitle()
         {
         global $param_locale;
         $db = &$this->db;
         return $db->getstring(20003)." - ".music_getRootTitle($param_locale);
         }

         function print_jsInclude()
         {
         }*/

         virtual void print_slist_preamble();
         virtual void print_list();
         virtual void print_rows();
         virtual void start_table();
         virtual void end_table();
         virtual void print_row(webserver::music::category * pcategory);

      };

   } // namespace music

} // namespace webserver