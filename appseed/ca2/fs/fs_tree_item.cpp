#include "framework.h"


namespace fs
{

   tree_item::tree_item()
   {
      m_iImage = -1;
      m_iImageSelected = 1;
   }


   int32_t tree_item::CompareArrangeByName( gen::tree_item * pitem1, gen::tree_item * pitem2, ::gen::tree_data * ptreedata)
   {
      
      if(typeid(*pitem1) == typeid(*pitem2) && typeid(*pitem1) == Sys(ptreedata->get_app()->m_psystem).type_info < tree_item > ())
      {
         return ((tree_item *) pitem1)->m_strName.CompareNoCase(((tree_item *) pitem2)->m_strName);
      }
      else
      {
         return strcmp(typeid(*pitem1).name(), typeid(*pitem2).name());
      }

   }

   int32_t tree_item::get_index() const
   {
      return m_iIndex;
   }

   bool tree_item::is_folder() const
   {
      return m_flags.is_signalized(FlagFolder);
   }



   string tree_item::get_text(gen::tree * ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
		return m_strName;
   }

   index tree_item::get_image(gen::tree * ptree)
   {
      if(ptree->is_selected(this))
      {
         return m_iImageSelected;
      }
      else
      {
         return m_iImage;
      }

   }


} // namespace fs


