#pragma once


namespace fs
{


   class CLASS_DECL_ca2 tree_data :
      public gen::tree_data
   {
   public:


      tree_data(::ca::application * papp);


      virtual ::gen::tree_item_data * on_allocate_item();
      virtual void on_delete_item(::gen::tree_item_data * pitem);


   };


} // namespace fs




