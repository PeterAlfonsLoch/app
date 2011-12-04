#pragma once

namespace fs
{


   class CLASS_DECL_ca2 tree_data :
      virtual public ex1::tree_data
   {
   public:

      tree_data(::ca::application * papp);

      virtual ::ex1::tree_item_data * on_allocate_item();
      virtual void on_delete_item(::ex1::tree_item_data * pitem);

   };


} // namespace fs

