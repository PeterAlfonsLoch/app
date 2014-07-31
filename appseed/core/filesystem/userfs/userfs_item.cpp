#include "framework.h"


namespace userfs
{

   item::item(::userfs::tree * ptree) :
      root(ptree->get_app()),
      m_ptree(ptree)
   {
      m_iImage = -1;
      m_iImageSelected = -1;
   }

   item::~item()
   {
   
   }
   


   index item::CompareArrangeByName(sp(::data::tree_item) * pitem1, sp(::data::tree_item)  * pitem2)
   {
      
      if(pitem1->m_p->m_ptree == pitem2->m_p->m_ptree)
      {
         return pitem1->m_p->m_pitem.cast < item >()->m_strName.CompareNoCase(pitem2->m_p->m_pitem.cast < item >()->m_strName);
      }
      else
      {
         return strcmp(typeid(pitem1->m_p).name(), typeid(pitem2->m_p).name());
      }

   }

   int32_t item::get_index() const
   {
      return m_iIndex;
   }

   bool item::is_folder() const
   {
      return m_flags.is_signalized(::fs::FlagFolder);
   }



   string item::data_item_get_text(object * pobject) const
   {

      UNREFERENCED_PARAMETER(pobject);

		return m_strName;

   }


   index item::data_item_get_image(object * pobject) const
   {
      if(m_ptree->is_selected(this))
      {
         if(m_iImageSelected < 0)
         {
            return m_ptree->m_iDefaultImageSelected;
         }
         return m_iImageSelected;
      }
      else
      {
         if(m_iImage < 0)
         {
            return m_ptree->m_iDefaultImage;
         }
         return m_iImage;
      }

   }

   image_list * item::data_item_get_image_list(object * pobject) const
   {

      return m_ptree->m_pimagelist;

   }


} // namespace userfs





