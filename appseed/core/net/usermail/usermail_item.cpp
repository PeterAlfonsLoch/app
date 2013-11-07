#include "framework.h"


namespace usermail
{


   string item::data_item_get_text(object * pobject)
   {

      UNREFERENCED_PARAMETER(pobject);

      return m_strName;

   }


   index item::data_item_get_image(::user::interaction * pui)
   {

      if(pui->is_selected(this))
      {
         return -1;
      }
      else
      {
         return -1;
      }

   }


} // namespace mail



