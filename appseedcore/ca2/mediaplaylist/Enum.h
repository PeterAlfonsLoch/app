#pragma once

enum EPlaylistPlay
{
   PlaylistPlaySuccess,              // the file has successfully started to play
   PlaylistPlayErrorBusy,            // another file is playing
   PlaylistPlayErrorContinue,        // there was an error opening the file, there is a hint to continue without that file
   PlaylistPlayErrorCancel,          // there was an error opening the file, there is a hint to cancel the playlist process
   PlaylistPlaySuccessBatched = PlaylistPlaySuccess,
};

namespace mediaplaylist
{

   enum ESetCurrentSongHint
   {
      SetCurrentSongHintDoPlay,
      SetCurrentSongHintPlayIfNotPlaying,
   };


} // namespace mediaplaylist


