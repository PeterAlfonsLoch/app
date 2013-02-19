#include "framework.h"


namespace fs
{

   void list_item_array::base_list_item_array::SoftSwap(index i1, index i2)
   {
      index iArrange = this->element_at(i1).m_iArrange;
      this->element_at(i1).m_iArrange = this->element_at(i2).m_iArrange;
      this->element_at(i2).m_iArrange = iArrange;
   }

   list_item & list_item_array::base_list_item_array::get_item(index i)
   {
      if(i < 0 || i >= this->get_count())
         throw "cannot recover";
      if(this->element_at(i).m_iArrange < 0 || this->element_at(i).m_iArrange >= this->get_count())
      {
         if(this->element_at(i).m_iIndex < 0 || this->element_at(i).m_iIndex >= this->get_count())
         {
            return this->element_at(i);
         }
         else
         {
            this->element_at(this->element_at(i).m_iIndex);
         }
      }
      return this->element_at(this->element_at(i).m_iArrange);
   }

   list_item_array::list_item_array(::ca::application * papp) :
      ca(papp)
   {
      m_itema.set_app(papp);
   }

   list_item_array::~list_item_array()
   {
   }

   void list_item_array::SetItemCount(count iCount)
   {
      m_itema.set_size(iCount);
   }

   void list_item_array::SetItemAt(index i, list_item & item)
   {
      item.m_iArrange = i;
      m_itema[i] = item;
   }

   list_item & list_item_array::get_item(index i)
   {
      return m_itema.get_item(i);
   }

   count list_item_array::get_count()
   {
      return m_itema.get_size();
   }

   count list_item_array::get_size()
   {
      return m_itema.get_size();
   }

   index list_item_array::get_upper_bound(count count)
   {
      return m_itema.get_upper_bound() - count;
   }

   void list_item_array::add_item(list_item &item)
   {
      m_itema.add(item);
      m_itema.element_at(this->get_size() - 1).m_iArrange = this->get_size() - 1;
   }

   index list_item_array::find_item_by_path(const char * pszPath)
   {
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         if(m_itema.element_at(i).m_strPath == pszPath)
            return i;
      }
      return -1;
   }

   void list_item_array::arrange(e_arrange earrange)
   {
      string str;
      int32_t iItem;
      for(int32_t iItem = 0; iItem < this->get_size(); iItem++)
      {
         str = get_item(iItem).m_strName;
      }
      switch(earrange)
      {
      case arrange_by_name:
         m_itema.QuickSort(
            &base_list_item_array::get_item,
            &list_item::CompareArrangeByName,
            &base_list_item_array::SoftSwap);
         break;
      default:
         break;
      }
      for(iItem = 0; iItem < this->get_size(); iItem++)
      {
         str = get_item(iItem).m_strName;
      }
   }


} // namespace fs

