//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


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

		return id(var::type_empty);
//      return ::aura::system::idEmpty;
   }

   
   ::user::document * view_container::get_view_document()
   {

      return ::user::impact::get_document(get_view());

   }


   void view_container::on_new_view_creator_data(view_creator_data * pcreatordata)
   {
      UNREFERENCED_PARAMETER(pcreatordata);
   }

} // namespace user
