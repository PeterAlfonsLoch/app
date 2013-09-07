#pragma once


namespace userfs
{


   class CLASS_DECL_ca2 tree_data :
      public ::data::tree_data
   {
   public:


      tree_data(sp(base_application) papp);


      virtual sp(::core::tree_item_data) on_allocate_item();


   };


} // namespace userfs




