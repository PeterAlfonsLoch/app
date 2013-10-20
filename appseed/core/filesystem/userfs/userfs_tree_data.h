#pragma once


namespace userfs
{


   class CLASS_DECL_CORE tree_data :
      public ::data::tree_data
   {
   public:


      tree_data(sp(base_application) papp);


      virtual sp(::data::tree_item_data) on_allocate_item();


   };


} // namespace userfs




