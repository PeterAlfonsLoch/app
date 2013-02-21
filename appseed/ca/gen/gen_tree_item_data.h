#pragma once


class image_list;


namespace gen
{


   class tree_item_data_ptr_array;
   class tree_data;
   class tree;


   class CLASS_DECL_ca tree_item_data
   {
   public:


      tree_data *                m_pdata;


      tree_item_data();
      virtual ~tree_item_data();

      virtual bool set_tree_data(tree_data * pdata);
      virtual tree_data * get_tree_data();

      virtual string get_text(tree * ptree);
      virtual index get_image(tree * ptree);
      virtual image_list * get_image_list(tree * ptree);

   };


   class CLASS_DECL_ca tree_item_data_ptr_array :
      public comparable_array < tree_item_data * >
   {
   public:


   };


} // namespace gen


