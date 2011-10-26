#include "StdAfx.h"


namespace netshareclient
{


   string tree_item::get_text(ex1::tree * ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      if(m_strLogin.is_empty())
         return m_strAddress;
      else
		   return m_strLogin;
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


} // namespace netshareclient