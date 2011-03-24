#pragma once

#include "filemanager/FileManagerFrame.h"

namespace syllomatter
{

   class CLASS_DECL_CA2_CUBE filemanager_frame :
      public FileManagerFrame
   {
   public:
      filemanager_frame(::ca::application * papp);
      virtual ~filemanager_frame();
   };

}//  namespace syllomatter