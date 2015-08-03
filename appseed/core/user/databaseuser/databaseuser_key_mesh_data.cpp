#include "framework.h"


namespace databaseuser
{


   data_key_mesh_data::data_key_mesh_data(::aura::application * papp) :
      object(papp),
      ::user::mesh_data(papp)
   {
   }

   data_key_mesh_data::~data_key_mesh_data()
   {
   }


   void data_key_mesh_data::_001GetItemText(::user::mesh_item * pitem)
   {
      stringa stra;
      if(!data_get(::aura::system::idEmpty, stra))
         return_(pitem->m_bOk, false)
      pitem->m_strText = stra[pitem->m_iItem];
      pitem->m_bOk = true;
   }

   void data_key_mesh_data::GetSel(::user::list * plist , stringa & stra)
   {
      stringa wstraTotal;
      if(!data_get(::aura::system::idEmpty, wstraTotal))
         return;
      ::user::list::range range;
      plist->_001GetSelection(range);
      for(index i = 0; i < range.get_item_count() ; i++)
      {
         ::user::list::item_range itemrange = range.ItemAt(i);
         for(index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {
            stra.add(wstraTotal[iItem]);
         }
      }
   }

   ::count data_key_mesh_data::_001GetItemCount()
   {
      stringa straTotal;
      if(!data_get(::aura::system::idEmpty, straTotal))
         return -1;
      return straTotal.get_size();
   }


   bool data_key_mesh_data::add_unique(const stringa & stra)
   {
      stringa straData;
      data_get(::aura::system::idEmpty, straData);
      straData.add_unique(stra);
      if(!data_set(::aura::system::idEmpty, straData))
         return false;
      return true;
   }

   bool data_key_mesh_data::remove(const stringa & stra)
   {
      stringa straData;
      if(!data_get(::aura::system::idEmpty, straData))
         return true;
      straData.remove(stra);
      if(!data_set(::aura::system::idEmpty, straData))
         return false;
      return true;
   }


} // namespace databaseuser



