#include "framework.h"


namespace user
{


   simple_list_data::simple_list_data(sp(::aura::application) papp) :
      element(papp),
      ::user::list_data(papp)
   {
      m_bEnable = true;
   }

   simple_list_data::~simple_list_data()
   {

   }

   void simple_list_data::_001GetItemText(::user::list_item * pitem)
   {

      if(!m_bEnable)
         return_(pitem->m_bOk, false);

      if(pitem->m_iSubItem < 0)
         return_(pitem->m_bOk, false);

      if(pitem->m_iSubItem >= m_array.get_size())
         return_(pitem->m_bOk, false);

      stringa & stra = m_array[pitem->m_iSubItem];

      if(pitem->m_iItem < 0)
         return_(pitem->m_bOk, false);

      if(pitem->m_iItem >= stra.get_size())
         return_(pitem->m_bOk, false);


      pitem->m_strText = stra.element_at(pitem->m_iItem);

      pitem->m_bOk = true;


   }

   void simple_list_data::set_item_text(int_ptr iItem, int_ptr iSubItem, const char * lpcsz)
   {

      while(iSubItem >= m_array.get_size())
      {
         m_array.add(new stringa());
      }

      m_array[iSubItem].set_at_grow(iItem, lpcsz);

   }

   void simple_list_data::set_item_text(list * plist, index iItem, index iSubItem, const char * lpcsz)
   {
      set_item_text(iItem, iSubItem, lpcsz);
      plist->_001OnUpdateItemCount();
   }

   void simple_list_data::Enable(bool bEnable)
   {
      m_bEnable = bEnable;
   }

   void simple_list_data::get_column_data(stringa & stra, int_ptr iColumn)
   {
      stra = m_array[iColumn];

   }

   void simple_list_data::get_data(stringa &stra)
   {
      get_column_data(stra, 0);
   }

   void simple_list_data::set_column_data(list * plist, stringa & stra, int_ptr iColumn)
   {
      m_array.set_at_grow(iColumn, new stringa(stra));
      for(int32_t iSubItem = 0; iSubItem < m_array.get_count(); iSubItem++)
      {
         if(iColumn != iSubItem)
         {
            m_array[iSubItem].set_size(stra.get_count());
         }
      }
      plist->_001OnUpdateItemCount();

   }

   void simple_list_data::set_data(list * plist, stringa &stra)
   {
      set_column_data(plist, stra, 0);
   }

   bool simple_list_data::remove_item(int_ptr iItem)
   {
      if(iItem < 0)
         return false;
      if(iItem >= m_array.get_size())
         return false;
      for(int32_t iSubItem = 0; iSubItem < m_array.get_size(); iSubItem++)
      {
         m_array[iSubItem].remove_at(iItem);
      }
      return true;
   }

   int_ptr simple_list_data::_001GetItemCount()
   {

      if(m_array.get_size() <= 0)
         return 0;
      else
         return m_array[0].get_size();

   }


   void simple_list_data::_001OnDeleteRange(::user::list::range & range)
   {
      
      index_array ia;

      range.get_item_indexes(ia);

      m_array._001RemoveIndexes(ia);

   }



} // namespace user


