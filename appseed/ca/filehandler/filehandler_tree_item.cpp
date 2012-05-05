#include "StdAfx.h"


namespace ca2
{


   namespace filehandler
   {


      string tree_item::get_text(ex1::tree * ptree)
      {
         UNREFERENCED_PARAMETER(ptree);
         return m_strTopic;
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
   
   
   } // namespace filehandler


} // namespace ca2


