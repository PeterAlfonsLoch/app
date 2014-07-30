#include "framework.h"


namespace data
{


   item::item()
   {
   }

   item::~item()
   {
   }

   string item::data_item_get_text(object * pobject) const
   {
      UNREFERENCED_PARAMETER(pobject);
      return "";
   }

   index item::data_item_get_image(object * pobject) const
   {
      UNREFERENCED_PARAMETER(pobject);
      return -1;
   }

   image_list * item::data_item_get_image_list(object * pobject) const
   {
      UNREFERENCED_PARAMETER(pobject);
      return NULL;
   }


   void item::data_item_on_fill_children(::data::tree_item * pitem)
   {

   }


} // namespace data



