#pragma once

namespace simpledb
{

   class CLASS_DECL_AXIS file_set :
      public ::file::set_sp,
      public ::database::client
   {
   public:
      file_set(::aura::application * papp);
      virtual ~file_set();

      virtual bool refresh();

      bool add_search(const char * pszSearchDirectory, bool bRecursive);

      virtual bool clear_search();

      DECL_GEN_SIGNAL(data_on_after_change);
   };

} // namespace simpledb