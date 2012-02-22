#pragma once


namespace webserver
{


   /////////////////////////////////////////////////////////////
   //    class MusicListClassPerformer
   //      Performer of a Category Music List
   /////////////////////////////////////////////////////////////

   namespace music
   {

      class CLASS_DECL_ca in2_list_artists :
         virtual public in2_list
      {
      public:


         var m_performera;
         var m_classname;
         var m_classid;
         var m_parentclass;
         var m_namequerycode;


         in2_list_artists(var classid, var namequerycode, var order, var target, var query = "");

         virtual void      print_js_include();
         virtual string    get_title();
         virtual void      print_list();
         virtual void      print_slist_preamble();
         virtual void      print_slist_closure();
         virtual void      printrows();
         virtual void      print_row(webserver::music:: performer * pperformer, index line);

      };


   } // namespace music


} // namespace webserver

