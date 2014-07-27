#include "framework.h"


namespace filemanager
{


   item_action::item_action()
   {

   }


   item_action::~item_action()
   {

   }


   bool item_action::open_file(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(itema);
      return false;
   }


} // namespace filemanager