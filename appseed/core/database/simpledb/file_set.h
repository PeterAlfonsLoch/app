#pragma once

namespace simpledb
{

   class CLASS_DECL_CORE file_set :
      public ::file::set_sp,
      public ::database::client
   {
   public:
      file_set(sp(::aura::application) papp);
      virtual ~file_set();

      virtual bool refresh();

      bool add_search(const char * pszSearchDirectory);

      virtual bool clear_search();

      DECL_GEN_VSIGNAL(data_on_after_change);
   };

} // namespace simpledb