#pragma once


namespace webserver
{


   namespace music
   {


      class CLASS_DECL_ca lyrics_song_in2_list :
         public in2_info_list
      {
      public:



         lyrics_song_in2_list(var songid, var pgid, var topic, var topictype);


         lyrics_song_in2_list(var id);


         virtual string get_list_title();


         virtual void print_row(int iIndex, ::webserver::music::song * psong, int line);

      };


   } // namespace music


} // namespace webserver


