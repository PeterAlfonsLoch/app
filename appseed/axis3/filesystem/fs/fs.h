#pragma once


namespace fs
{

   
   enum e_arrange
   {
      
      arrange_by_name
         
   };
   

   enum e_flag
   {
      
      FlagInZip,
      FlagFolder,
      FlagFolderEx001,
      FlagFolderEx001Calc,
      FlagHasSubFolder,
      FlagHasSubFolderUnknown
         
   };
   

} // namespace fs



#include "fs_item.h"
#include "fs_item_array.h"

#include "fs_data.h"
#include "fs_set.h"
#include "fs_ifs_file.h"
#include "fs_ifs.h"
#include "fs_native_fs.h"
#include "fs_remote_native_file.h"
#include "fs_remote_native_fs.h"
#include "fs_link.h"

#include "fs_fs.h"


