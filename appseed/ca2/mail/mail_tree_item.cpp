#include "framework.h"


namespace mail
{


   string tree_item_data::get_text(sp(::ca::tree) ptree)
   {

      UNREFERENCED_PARAMETER(ptree);

      return m_strName;

   }


   index tree_item_data::get_image(sp(::ca::tree) ptree)
   {

      if(ptree->is_tree_item_selected(this))
      {
         return -1;
      }
      else
      {
         return -1;
      }

   }


} // namespace mail



