#include "StdAfx.h"

namespace user
{

   simple_list_data::simple_list_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      ::user::list_data(papp)
   {
      m_bEnable = true;
   }

   simple_list_data::~simple_list_data()
   {

   }

   bool simple_list_data::_001GetItemText(
      list * plist,
      string &str,
      INT_PTR iItem,
      INT_PTR iSubItem, 
      INT_PTR iListItem)
   {
      UNREFERENCED_PARAMETER(plist);
      UNREFERENCED_PARAMETER(iListItem);
      if(!m_bEnable)
         return false;
      if(iItem < 0)
         return false;
      if(iItem >= m_array.get_size())
         return false;
      stringa & stra = m_array.element_at(iItem);
      if(iSubItem < 0)
         return false;
      if(iSubItem >= stra.get_size())
         return false;
      
      str = stra.element_at(iSubItem);
      return true;
   }

   void simple_list_data::SetItemText(INT_PTR iItem, INT_PTR iSubItem, const char * lpcsz)
   {

      while(iItem >= m_array.get_size())
      {
         m_array.add(stringa());
      }

      stringa & stra = m_array.element_at(iItem);

      while(iSubItem >= stra.get_size())
      {
         stra.add(L"");
      }

      stra.set_at(iSubItem, lpcsz);
   }

   void simple_list_data::SetItemText(list * plist, index iItem, index iSubItem, const char * lpcsz)
   {
      SetItemText(iItem, iSubItem, lpcsz);
      plist->_001OnUpdateItemCount();
   }

   void simple_list_data::Enable(bool bEnable)
   {
      m_bEnable = bEnable;
   }

   void simple_list_data::GetColumnData(stringa &stra, INT_PTR iColumn)
   {
      for(int i = 0; i < m_array.get_size(); i++)
      {
         stra.add(m_array[i][iColumn]);
      }

   }

   void simple_list_data::get_data(stringa &stra)
   {
      GetColumnData(stra, 0);
   }

   void simple_list_data::SetColumnData(list * plist, stringa &stra, INT_PTR iColumn)
   {
      for(int i = 0; i < stra.get_size(); i++)
      {
         SetItemText(i, iColumn, stra[i]);
      }
      plist->_001OnUpdateItemCount();

   }

   void simple_list_data::set_data(list * plist, stringa &stra)
   {
      SetColumnData(plist, stra, 0);
   }

   bool simple_list_data::RemoveItem(INT_PTR iItem)
   {
      if(iItem < 0)
         return false;
      if(iItem >= m_array.get_size())
         return false;
      m_array.remove_at(iItem);
      return true;
   }

   INT_PTR simple_list_data::_001GetItemCount()
   {
      return m_array.get_size();
   }

} // namespace user
