#include "StdAfx.h"

namespace ex1
{

   tree_data::tree_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp)
   {
   }

   tree_data::~tree_data()
   {
      finalize();
   }

   bool tree_data::initialize()
   {
      return true;
   }

   bool tree_data::finalize()
   {
      return true;
   }

   bool tree_data::contains(tree_item_data * pitem)
   {
      return m_itemdataptra.contains(pitem);
   }

   tree_item_data * tree_data::_allocate_item()
   {
      tree_item_data * pdata = on_allocate_item();
      if(pdata == NULL)
         return NULL;
      m_itemdataptra.add(pdata);
      return pdata;
   }
   
   bool tree_data::_delete_item(tree_item_data * pitem)
   {
      if(!contains(pitem))
         return false;
      on_delete_item(m_itemdataptra.last_element());
      m_itemdataptra.remove(pitem);
      return true;
   }

   ex1::tree_item_data * tree_data::on_allocate_item()
   {
      return new tree_item_data;
   }

   void tree_data::on_delete_item(ex1::tree_item_data * pitem)
   {
      delete pitem;
   }


} // namespace ex1