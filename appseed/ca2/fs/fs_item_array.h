#pragma once


namespace fs
{

   class CLASS_DECL_ca2 item_array :
      public array_ptr_alloc < item, item & >
   {
   public:
      var get_var_file() const;
      var get_var_query() const;
   };


} // namespace fs

