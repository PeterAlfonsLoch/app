#pragma once


namespace mediaplaylist
{

   enum e_play
   {
      play_success,              // the file has successfully started to play
      play_error_busy,            // another file is playing
      play_error_continue,        // there was an error opening the file, there is a hint to continue without that file
      play_error_cancel,          // there was an error opening the file, there is a hint to cancel the playlist process
      play_success_batched,
   };


   enum e_hint
   {
      hint_do_play,
      hint_play_if_not_playing,
   };


} // namespace mediaplaylist


