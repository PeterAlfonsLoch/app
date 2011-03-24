#include "StdAfx.h"

namespace user
{

   get_view::get_view()
   {
   }

   get_view::~get_view()
   {
   }

   ::user::interaction * get_view::get_view_uie()
   {
      return NULL;
   }

   id get_view::get_view_id()
   {
      return ::ca::system::idEmpty;
   }

   document * get_view::get_view_document()
   {
      return view::get_document(get_view_uie());
   }

} // namespace user