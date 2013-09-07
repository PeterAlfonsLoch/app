#include "framework.h"


namespace usermail
{


   string tree_item_data::get_text(sp(::core::tree) ptree)
   {

      UNREFERENCED_PARAMETER(ptree);

      return m_strName;

   }


   index tree_item_data::get_image(sp(::core::tree) ptree)
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


} // namespace mail



