#pragma once


#include "ca/simpleuser/simpleuser.h"


namespace fs
{

   enum e_arrange
   {
      arrange_by_name,
   };

   enum e_flag
   {
      FlagInZip,
      FlagFolder,
      FlagFolderEx001,
      FlagFolderEx001Calc,
      FlagHasSubFolder,
      FlagHasSubFolderUnknown,
   };

} // namespace fs


#include "fs_item.h"
#include "fs_item_array.h"

#include "fs_data.h"
#include "fs_set.h"
#include "ifs_file.h"
#include "ifs.h"
#include "native_fs.h"

#include "fs_document.h"

#include "fs_list_item.h"
#include "fs_list_item_array.h"
#include "fs_list_data.h"
#include "fs_list_interface.h"
#include "fs_list.h"


#include "fs_tree_item.h"
#include "fs_tree_data.h"
#include "fs_tree_interface.h"
#include "fs_tree.h"

#include "fs_main_view.h"

#include "fs_application.h"


