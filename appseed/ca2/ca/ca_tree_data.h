#pragma once


class image_list;


namespace ca
{


   class tree_data;
   class tree;


   class CLASS_DECL_ca tree_data :
      public ::ca::data
   {
   public:


      tree_item_data_ptr_array            m_itemdataptra;
      sp(image_list)                      m_pimagelist;


      tree_data(sp(::ca::application) papp);
      virtual ~tree_data();


      //virtual bool initialize_data();
      //virtual bool finalize_data();


      bool contains(sp(tree_item_data) pitem);

      virtual sp(tree_item_data) _allocate_item();
      //virtual bool _delete_item(sp(tree_item_data) pitem);


   protected:


      virtual sp(tree_item_data) on_allocate_item();
      //virtual void on_delete_item(sp(tree_item_data) pitem);


   };


} // namespace ca


