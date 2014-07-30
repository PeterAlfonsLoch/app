#include "framework.h"


namespace usermail
{


   item::item(tree * ptree) :
      m_ptree(ptree)
   {

   }


   item::~item()
   {

   }


   string item::data_item_get_text(object * pobject) const
   {

      UNREFERENCED_PARAMETER(pobject);

      return m_strName;

   }


   index item::data_item_get_image(object * pobject) const
   {

/*      if(m_ptree->is_selected(this))
      {
         return -1;
      }
      else
      {
         return -1;
      }
      */

      return -1;

   }

   image_list * item::data_item_get_image_list(object * pobject) const
   {

      /*return m_ptree->get_image_list();*/
      return NULL;

   }

} // namespace mail



