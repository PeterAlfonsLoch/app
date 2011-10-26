#include "StdAfx.h"


namespace syllomatter
{

   filemanager_frame::filemanager_frame(::ca::application * papp) :
         ca(papp),
         window_frame::WorkSetClientInterface(papp),
         userbase::frame_window_interface(papp),
         userbase::frame_window(papp),
         FileManagerFrame (papp)
      {
      }
      filemanager_frame::~filemanager_frame()
      {
      }

}//  namespace syllomatter