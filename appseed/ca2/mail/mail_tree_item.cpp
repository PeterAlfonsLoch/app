#include "framework.h"


namespace mail
{


   string tree_item::get_text(ca::tree * ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      return m_strName;
   }

   index tree_item::get_image(ca::tree * ptree)
   {
      if(ptree->is_selected(this))
      {
         return -1;
      }
      else
      {
         return -1;
      }

   }


} // namespace mail