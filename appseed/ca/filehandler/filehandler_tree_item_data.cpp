#include "framework.h"




namespace filehandler
{


   string tree_item_data::get_text(sp(::ca::tree) ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      return m_strTopic;
   }

   index tree_item_data::get_image(sp(::ca::tree) ptree)
   {
      if(ptree->is_tree_item_data_selected(this))
      {
         return -1;
      }
      else
      {
         return -1;
      }

   }
   
   
} // namespace filehandler




