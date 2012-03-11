#include "StdAfx.h"


namespace ca2
{


   namespace filehandler
   {


      tree_data::tree_data(::ca::application * papp) :
         ca(papp),
         ex1::tree_data(papp)
      {
      }


      ::ex1::tree_item_data * tree_data::on_allocate_item()
      {
         return new ::ca2::filehandler::tree_item();
      }

      void tree_data::on_delete_item(::ex1::tree_item_data * pitem)
      {
         delete (::ca2::filehandler::tree_item *) pitem;
      }
   
   
   } // namespace filehandler


} // namespace ca2


