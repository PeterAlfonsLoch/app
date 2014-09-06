#include "axis/user/user.h"

namespace user
{

   view_container::view_container()
   {
   }

   view_container::~view_container()
   {
   }

   sp(::user::interaction) view_container::get_view()
   {
      return NULL;
   }

   id view_container::get_view_id()
   {
   return id(var::type_empty);
//      return ::axis::system::idEmpty;
   }

   sp(::user::document) view_container::get_view_document()
   {
      return impact::get_document(get_view());
   }

   void view_container::on_new_view_creator_data(view_creator_data * pcreatordata)
   {
      UNREFERENCED_PARAMETER(pcreatordata);
   }

} // namespace user
