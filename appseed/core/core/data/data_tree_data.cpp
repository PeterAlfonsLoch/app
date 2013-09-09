#include "framework.h"


namespace data
{


   tree_data::tree_data(sp(base_application) papp) :
      element(papp),
      ::data::data(papp)
   {

   }


   tree_data::~tree_data()
   {

   }


   bool tree_data::contains(sp(tree_item_data) pitem)
   {

      return m_itemdataptra.contains(pitem);

   }


   sp(tree_item_data) tree_data::_allocate_item()
   {

      sp(tree_item_data) pdata = on_allocate_item();

      if(pdata == NULL)
         return NULL;

      m_itemdataptra.add(pdata);

      return pdata;

   }

   sp(tree_item_data) tree_data::on_allocate_item()
   {

      return canew(::data::tree_item_data());

   }


} // namespace data




