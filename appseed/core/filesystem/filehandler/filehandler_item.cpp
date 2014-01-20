#include "framework.h"




namespace filehandler
{


   string item::data_item_get_text(object * pobject) const
   {

      UNREFERENCED_PARAMETER(pobject);

      return m_strTopic;

   }


   index item::data_item_get_image(object * pobject) const
   {

      return -1;

   }
   
   
} // namespace filehandler




