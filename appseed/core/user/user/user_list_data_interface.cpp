#include "framework.h"


namespace user
{


   list_data::list_data(sp(::aura::application) papp) :
      element(papp),
      ::data::data(papp)
   {
   }

   list_data::~list_data()
   {
   }


   void list_data::_001GetItemImage(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
   }

   void list_data::_001GetGroupText(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
   }

   void list_data::_001GetGroupImage(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
   }

   ::count list_data::_001GetGroupCount()
   {
      return -1;
   }

   ::count list_data::_001GetGroupMetaItemCount(index iGroup)
   {
      UNREFERENCED_PARAMETER(iGroup);
      return 0;
   }

   void list_data::_001OnDeleteRange(::user::list::range & range)
   {
      UNREFERENCED_PARAMETER(range);
   }

} // namespace user