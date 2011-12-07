#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca karaoke_song_in2_list :
         public in2_info_list
      {
      public:


         karaoke_song_in2_list(var id);


         virtual string get_list_title();

         virtual void print_list();



         virtual void printrows();

         virtual void print_row(int iIndex, ::webserver::music::song * psong, int line);
         virtual void print_slist_closure();
      };


   } // namespace music


} // namespace webserver

