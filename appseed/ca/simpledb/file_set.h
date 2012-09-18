#pragma once

namespace simpledb
{

   class CLASS_DECL_ca file_set :
      public ex2::file_set_sp,
      public ::database::client
   {
   public:
      file_set(::ca::application * papp);
      virtual ~file_set();

      virtual bool refresh();

      bool add_search(const char * pszSearchDirectory);

      virtual bool clear_search();

      DECL_GEN_VSIGNAL(data_on_after_change)
   };

} // namespace simpledb