#include "StdAfx.h"


namespace fs
{

   tree_item::tree_item()
   {
      m_iImage = -1;
   }


   int tree_item::CompareArrangeByName(ex1::tree_item * pitem1, ex1::tree_item * pitem2, void * pparam)
   {
      UNREFERENCED_PARAMETER(pparam);
      if(typeid(*pitem1) == typeid(*pitem2) && typeid(*pitem1) == typeid(tree_item))
      {
         return ((tree_item *) pitem1)->m_strName.CompareNoCase(((tree_item *) pitem2)->m_strName);
      }
      else
      {
         return strcmp(typeid(*pitem1).raw_name(), typeid(*pitem2).raw_name());
      }
   }

   int tree_item::get_index() const
   {
      return m_iIndex;
   }

   bool tree_item::is_folder() const
   {
      return m_flags.is_signalized(FlagFolder);
   }



   string tree_item::get_text(ex1::tree * ptree)
   {
		return m_strName;
   }

   index tree_item::get_image(ex1::tree * ptree)
   {
      if(ptree->is_selected(this))
      {
         return -1;
      }
      else
      {
         return -1;
      }

   }


} // namespace fs


