#include "framework.h"


namespace user
{


   menu_base_item::menu_base_item(sp(base_application) papp) :
      element(papp)
   {

   }


   menu_base_item::~menu_base_item()
   {

   }


   bool menu_base_item::create_menu(const stringa & straCommand, const stringa & straCommandTitle)
   {

      throw interface_only_exception(get_app());

      return false;

   }

   bool menu_base_item::load_menu(sp(::xml::node) lpnode)
   {

      throw interface_only_exception(get_app());

      return false;

   }


} // namespace user




