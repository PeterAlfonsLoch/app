#pragma once


namespace fs
{

   
   enum e_arrange
   {
      
      arrange_by_name
         
   };
   

   enum e_flag
   {
      
      FlagInZip = 1 << 0,
      FlagFolder = 1 << 1,
      FlagFolderEx001 = 1 << 2,
      FlagFolderEx001Calc = 1 << 3,
      FlagHasSubFolder = 1 << 4,
      FlagHasSubFolderUnknown = 1 << 5
         
   };
   

} // namespace fs



#include "fs_item.h"
#include "fs_item_array.h"

#include "fs_data.h"
#include "fs_set.h"
#include "fs_ifs.h"
#include "fs_native_fs.h"
#include "fs_remote_native_fs.h"
#include "fs_link.h"

#include "fs_fs.h"


