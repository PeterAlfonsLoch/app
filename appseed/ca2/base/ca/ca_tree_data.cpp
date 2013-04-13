#include "framework.h"


namespace ca
{


   tree_data::tree_data(sp(::ca::application) papp) :
      ca(papp),
      ::ca::data(papp)
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

      if(pdata == ::null())
         return ::null();

      m_itemdataptra.add(pdata);

      return pdata;

   }

      sp(tree_item_data) tree_data::on_allocate_item()
      {

            return canew(::ca::tree_item_data());

      }





} // namespace ca
