#include "framework.h"


namespace filemanager
{


   folder_list_data::folder_list_data(sp(::aura::application) papp) :
      element(papp),
      ::user::list_data(papp)
   {
   }

   folder_list_data::~folder_list_data()
   {
   }




   void folder_list_data::_001GetItemText(::user::list_item * pitem)
   {
      if(pitem->m_iSubItem == 0)
      {
         stringa stra;
         if(!data_get(::base::system::idEmpty, ::base::system::idEmpty, stra))
         {
            pitem->m_bOk = false;
            return;
         }
         pitem->m_strText = stra[pitem->m_iItem];
      }
      else if(pitem->m_iSubItem == 1)
      {
         bool_array ba;
         if(!data_get("recursive", ::base::system::idEmpty, ba))
         {
            pitem->m_bOk = false;
            return;
         }
         bool b = ba[pitem->m_iItem];
         if(b)
         {
            pitem->m_strText = "Recursive";
         }
         else
         {
            pitem->m_strText.Empty();
         }
      }
      pitem->m_bOk = true;
   }

   void folder_list_data::GetSel(::user::list * plist , stringa & stra)
   {
      stringa wstraTotal;
      if(!data_get(::base::system::idEmpty, ::base::system::idEmpty, wstraTotal))
         return;
      ::user::list::range range;
      plist->_001GetSelection(range);
      for(index i = 0; i < range.get_item_count() ; i++)
      {
         ::user::list::item_range itemrange = range.ItemAt(i);
         for(index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {
            if(iItem >= 0 && iItem <= wstraTotal.get_upper_bound())
            {
               stra.add(wstraTotal[iItem]);
            }
         }
      }
   }

   ::count folder_list_data::_001GetItemCount()
   {
      stringa straTotal;
      if(!data_get(::base::system::idEmpty, ::base::system::idEmpty, straTotal))
         return -1;
      return straTotal.get_size();
   }


   bool folder_list_data::add_unique(const stringa & stra, bool_array & baRecursive)
   {
      stringa straData;
      data_get(::base::system::idEmpty, ::base::system::idEmpty, straData);
      bool_array baData;
      data_get("recursive", ::base::system::idEmpty, baData);
      for(int32_t i = 0; i < stra.get_count(); i++)
      {
         if(!straData.contains(stra[i]))
         {
            straData.add(stra[i]);
            if(i <= baRecursive.get_upper_bound())
            {
               baData.add(baRecursive[i]);
            }
         }
      }
      while(baData.get_size() < straData.get_size())
      {
         baData.add(true); // default bred, broad, expansive
      }
      while(baData.get_size() > straData.get_size())
      {
         baData.remove_last();
      }
      if(!data_set(::base::system::idEmpty, ::base::system::idEmpty, straData))
         return false;
      if(!data_set("recursive", ::base::system::idEmpty, baData))
         return false;
      return true;
   }

   bool folder_list_data::remove(const stringa & stra)
   {
      stringa straData;
      if(!data_get(::base::system::idEmpty, ::base::system::idEmpty, straData))
         return true;
      bool_array baData;
      data_get("recursive", ::base::system::idEmpty, baData);
      index iFind;
      for(int32_t i = 0; i < stra.get_count(); i++)
      {
         while((iFind = straData.find_first(stra[i])) >= 0)
         {
            straData.remove_at(iFind);
            if(iFind < baData.get_size())
            {
               baData.remove_at(iFind);
            }
         }
      }
      while(baData.get_size() < straData.get_size())
      {
         baData.add(true); // default bred, broad, expansive
      }
      while(baData.get_size() > straData.get_size())
      {
         baData.remove_last();
      }
      if(!data_set(::base::system::idEmpty, ::base::system::idEmpty, straData))
         return false;
      if(!data_set("recursive", ::base::system::idEmpty, baData))
         return false;

      return true;

   }


} // namespace filemanager



