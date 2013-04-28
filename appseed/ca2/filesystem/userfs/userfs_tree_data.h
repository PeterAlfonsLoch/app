#pragma once


namespace userfs
{


   class CLASS_DECL_ca2 tree_data :
      public ::ca::tree_data
   {
   public:


      tree_data(sp(::ca::application) papp);


      virtual sp(::ca::tree_item_data) on_allocate_item();


   };


} // namespace userfs




