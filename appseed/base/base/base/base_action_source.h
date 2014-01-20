#pragma once


namespace action
{


   enum e_source
   {

      source_none       = 0x00000000,

      source_clear      = 0x00000001,
      source_load       = 0x00000002,
      source_assign     = 0x00000004,
      source_cast       = 0x00000008,
      source_submit     = 0x00000010,
      source_undo       = 0x00000020,
      source_redo       = 0x00000040,
      source_copy       = 0x00000080,
      source_cut        = 0x00000100,
      source_paste      = 0x00000200,
      source_sync       = 0x00000400,
      source_selection  = 0x00000800,
      source_drop       = 0x00001000,
      source_initialize = 0x00002000,
      source_refresh    = 0x00004000,

      source_operator   = 0x04000000,
      source_system     = 0x08000000,
      source_default    = 0x10000000,
      source_data       = 0x20000000,
      source_database   = 0x40000000,
      source_user       = 0x80000000

   };



} // namespace action




