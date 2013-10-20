#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE tree_data :
      virtual public ::data::tree_data
   {
   public:


      tree_data(sp(base_application) papp);


      virtual sp(::data::tree_item_data) on_allocate_item();
      virtual void on_delete_item(sp(::data::tree_item_data) pitem);


   };


} // namespace filehandler






