#include "StdAfx.h"

namespace user
{

   view_container::view_container()
   {
   }

   view_container::~view_container()
   {
   }

   ::user::interaction * view_container::get_view()
   {
      return NULL;
   }

   id view_container::get_view_id()
   {
      return ::radix::system::idEmpty;
   }

   ::user::document_interface * view_container::get_view_document()
   {
      return view::get_document(get_view());
   }

   void view_container::on_new_view_creator_data(view_creator_data * pcreatordata)
   {
      UNREFERENCED_PARAMETER(pcreatordata);
   }

} // namespace user