#include "framework.h"


namespace userfs
{

   void list_item_array::base_list_item_array::SoftSwap(index i1, index i2)
   {
      index iArrange = this->element_at(i1)->m_iArrange;
      this->element_at(i1)->m_iArrange = this->element_at(i2)->m_iArrange;
      this->element_at(i2)->m_iArrange = iArrange;
   }

   list_item & list_item_array::base_list_item_array::get_item(index i, index (* fCompare)(sp(list_item) *, sp(list_item) *))
   {
      return *this->element_at(i, fCompare);
   }

   list_item_array::list_item_array(sp(::aura::application) papp) :
      element(papp)
   {
      m_itema.set_app(papp);
      m_pfnCompare = &BaseNullCompare < sp(list_item) >;
   }

   list_item_array::~list_item_array()
   {
   }

   list_item & list_item_array::get_item(index i)
   {
      return m_itema.get_item(i, m_pfnCompare);
   }

   ::count list_item_array::get_count()
   {
      return m_itema.get_size();
   }

   ::count list_item_array::get_size()
   {
      return m_itema.get_size();
   }

   index list_item_array::get_upper_bound(::count count)
   {
      return m_itema.get_size() + count;
   }

   void list_item_array::add_item(list_item & item)
   {

      sp(list_item) spitem(new list_item(item));

      m_itema.add(spitem);

      spitem->m_iArrange = this->get_size() - 1;

   }

   index list_item_array::find_item_by_path(const char * pszPath)
   {
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         if(m_itema.element_at(i)->m_strPath == pszPath)
            return i;
      }
      return -1;
   }

   void list_item_array::arrange(::fs::e_arrange earrange)
   {
      switch(earrange)
      {
      case ::fs::arrange_by_name:
         m_pfnCompare = &list_item::CompareArrangeByName;
         break;
      default:
         m_pfnCompare = &BaseNullCompare < sp(list_item) >;
         break;
      }
   }


} // namespace userfs




