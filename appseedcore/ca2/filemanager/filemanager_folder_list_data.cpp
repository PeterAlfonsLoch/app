#include "StdAfx.h"

namespace filemanager
{

   folder_list_data::folder_list_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      ::user::list_data(papp)
   {
   }

   folder_list_data::~folder_list_data(void)
   {
   }


   bool folder_list_data::_001GetItemText(
         ::user::list * plist,
         string &str,
         index iItem,
         index iSubItem, 
         index iListItem)
   {
      UNREFERENCED_PARAMETER(plist);
      UNREFERENCED_PARAMETER(iListItem);
      if(iSubItem == 0)
      {
         stringa stra;
         if(!data_get(::ca::system::idEmpty, ::ca::system::idEmpty, stra))
            return false;
         str = stra[iItem];
      }
      else if(iSubItem == 1)
      {
         bool_array ba;
         if(!data_get("recursive", ::ca::system::idEmpty, ba))
            return false;
         bool b = ba[iItem];
         if(b)
         {
            str = "Recursive";
         }
         else
         {
            str.Empty();
         }
      }
      return true;
   }

   void folder_list_data::GetSel(::user::list * plist , stringa & stra)
   {
      stringa wstraTotal;
      if(!data_get(::ca::system::idEmpty, ::ca::system::idEmpty, wstraTotal))
         return;
      ::user::list::Range range;
      plist->_001GetSelection(range);
      for(index i = 0; i < range.get_item_count() ; i++)
      {
         ::user::list::ItemRange itemrange = range.ItemAt(i);
         for(index iItem = itemrange.GetLBound(); iItem <= itemrange.GetUBound(); iItem++)
         {
            stra.add(wstraTotal[iItem]);
         }
      }
   }

   count folder_list_data::_001GetItemCount()
   {
      stringa straTotal;
      if(!data_get(::ca::system::idEmpty, ::ca::system::idEmpty, straTotal))
         return -1;
      return straTotal.get_size();
   }


   bool folder_list_data::add_unique(const stringa & stra, bool_array & baRecursive)
   {
      stringa straData;
      data_get(::ca::system::idEmpty, ::ca::system::idEmpty, straData);
      bool_array baData;
      data_get("recursive", ::ca::system::idEmpty, baData);
      for(int i = 0; i < stra.get_count(); i++)
      {
         if(!straData.contains(stra[i]))
         {
            straData.add(stra[i]);
            baData.add(baRecursive[i]);
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
      if(!data_set(::ca::system::idEmpty, ::ca::system::idEmpty, straData))
         return false;
      if(!data_set("recursive", ::ca::system::idEmpty, baData))
         return false;
      return true;
   }

   bool folder_list_data::remove(const stringa & stra)
   {
      stringa straData;
      if(!data_get(::ca::system::idEmpty, ::ca::system::idEmpty, straData))
         return true;
      bool_array baData;
      data_get("recursive", ::ca::system::idEmpty, baData);
      int iFind;
      for(int i = 0; i < stra.get_count(); i++)
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
      if(!data_set(::ca::system::idEmpty, ::ca::system::idEmpty, straData))
         return false;
      if(!data_set("recursive", ::ca::system::idEmpty, baData))
         return false;
      return true;
   }

} // namespace filemanager