#pragma once

namespace mail
{


   class CLASS_DECL_ca2 tree_data :
      virtual public ::ca::tree_data
   {
   public:

      tree_data(::ca::application * papp);

      virtual ::ca::tree_item_data * on_allocate_item();
      virtual void on_delete_item(::ca::tree_item_data * pitem);

   };


} // namespace mail