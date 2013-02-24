#include "framework.h"




namespace filehandler
{


   string tree_item::get_text(ca::tree * ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      return m_strTopic;
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
   
   
} // namespace filehandler




