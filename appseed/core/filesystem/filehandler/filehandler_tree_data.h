#pragma once


namespace filehandler
{


   class CLASS_DECL_ca2 tree_data :
      virtual public ::data::tree_data
   {
   public:


      tree_data(sp(base_application) papp);


      virtual sp(::core::tree_item_data) on_allocate_item();
      virtual void on_delete_item(sp(::core::tree_item_data) pitem);


   };


} // namespace filehandler






