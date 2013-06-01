#include "framework.h"

namespace ca
{


   tree_item_data::tree_item_data()
   {
   }

   tree_item_data::~tree_item_data()
   {
   }

   bool tree_item_data::set_tree_data(sp(tree_data) pdata)
   {
      m_pdata = pdata;
      return true;
   }

   sp(tree_data) tree_item_data::get_tree_data()
   {
      return m_pdata;
   }

   string tree_item_data::get_text(sp(tree) ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      return "";
   }

   index tree_item_data::get_image(sp(tree) ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      return -1;
   }

   sp(image_list) tree_item_data::get_image_list(sp(tree) ptree)
   {
      if(ptree == NULL)
         return NULL;
      return ptree->get_image_list();
   }


} // namespace ca