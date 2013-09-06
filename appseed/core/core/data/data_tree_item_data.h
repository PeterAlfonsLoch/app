#pragma once


class image_list;


namespace data
{


   class tree_item_data_ptr_array;
   class tree_data;
   class tree;


   class CLASS_DECL_ca2 tree_item_data :
      virtual public root
   {
   public:


      sp(tree_data)                m_pdata;


      tree_item_data();
      virtual ~tree_item_data();

      virtual bool set_tree_data(sp(tree_data) pdata);
      virtual sp(tree_data) get_tree_data();

      virtual string get_text(sp(tree) ptree);
      virtual index get_image(sp(tree) ptree);
      virtual sp(image_list) get_image_list(sp(tree) ptree);

   };


   class CLASS_DECL_ca2 tree_item_data_ptr_array :
      public spa(tree_item_data)
   {
   public:


   };


} // namespace ca2


