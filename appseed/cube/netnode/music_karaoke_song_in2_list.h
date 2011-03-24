#pragma once

namespace music
{

   class CLASS_DECL_CA2_CUBE karaoke_song_in2_list :
      public in2_info_list
   {
   public:
      virtual string get_list_title();
      
      
      karaoke_song_in2_list(var id);
      
      
      virtual void print_list();
      
      
   
      virtual void printrows();
      
      virtual void print_row(int iIndex, ::music::song * psong, int line);
      virtual void print_slist_closure();
   };
   
} // namespace music