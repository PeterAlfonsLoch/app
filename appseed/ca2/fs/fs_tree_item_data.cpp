#include "framework.h"


namespace fs
{

   tree_item_data::tree_item_data()
   {
      m_iImage = -1;
      m_iImageSelected = 1;
   }


   int32_t tree_item_data::CompareArrangeByName(sp(::ca::tree_item) & item1, sp(::ca::tree_item) & item2)
   {
      
      if(item1->m_ptreedata == item2->m_ptreedata)
      {
         return item1->m_pitemdata.cast < tree_item_data >()->m_strName.CompareNoCase(item2->m_pitemdata.cast < tree_item_data >()->m_strName);
      }
      else
      {
         return strcmp(typeid(item1.m_p).name(), typeid(item2.m_p).name());
      }

   }

   int32_t tree_item_data::get_index() const
   {
      return m_iIndex;
   }

   bool tree_item_data::is_folder() const
   {
      return m_flags.is_signalized(FlagFolder);
   }



   string tree_item_data::get_text(sp(::ca::tree) ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
		return m_strName;
   }

   index tree_item_data::get_image(sp(::ca::tree) ptree)
   {
      if(ptree->is_tree_item_data_selected(this))
      {
         return m_iImageSelected;
      }
      else
      {
         return m_iImage;
      }

   }


} // namespace fs


