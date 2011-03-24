#pragma once

#include "kar/KaraokeBouncingBall.h"
#include "mediaplaylist/PlaylistCentralCallbackInterface.h"

#define ATTENTION ASSERT(FALSE);


namespace vmsp
{
   enum EView
   {
      ViewAudioSpectrum,
      ViewFileManager,
      ViewPlaylist,
   };
} // namespace vmsp


#include "XfplayerViewUpdateHint.h"
#include "XfplayerDoc.h"
#include "XfplayerView.h"
#include "KaraokeSDIFrame.h"
#include "main_frame.h"
#include "application.h"



