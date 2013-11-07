#include "framework.h"


namespace data
{


   item::item()
   {
   }

   item::~item()
   {
   }

   string item::data_item_get_text(object * pobject)
   {
      UNREFERENCED_PARAMETER(pobject);
      return "";
   }

   index item::data_item_get_image(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      return -1;
   }

   sp(image_list) item::data_item_get_image_list(::user::interaction * pui)
   {
      if (pui == NULL)
         return NULL;
      return pui->get_image_list();
   }


} // namespace data



