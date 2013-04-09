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
   

   bool tree_data::_delete_item(sp(tree_item_data) pitem)
   {

      if(!contains(pitem))
         return false;

      on_delete_item(m_itemdataptra.last_element());

      m_itemdataptra.remove(pitem);

      return true;

   }


   sp(::ca::tree_item_data) tree_data::on_allocate_item()
   {

      return new tree_item_data;

   }


   void tree_data::on_delete_item(sp(::ca::tree_item_data) pitem)
   {
      delete pitem;
   }


} // namespace ca