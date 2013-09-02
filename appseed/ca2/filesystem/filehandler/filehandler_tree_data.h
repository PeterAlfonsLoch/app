#pragma once


namespace filehandler
{


   class CLASS_DECL_ca2 tree_data :
      virtual public ::ca2::tree_data
   {
   public:


      tree_data(sp(::application) papp);


      virtual sp(::ca2::tree_item_data) on_allocate_item();
      virtual void on_delete_item(sp(::ca2::tree_item_data) pitem);


   };


} // namespace filehandler






