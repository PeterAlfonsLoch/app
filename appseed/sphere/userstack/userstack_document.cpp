#include "framework.h"


namespace userstack
{


   document::document(sp(::base::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::user::object(papp)
   {
   }

   bool document::on_new_document()
   {
      if (!::user::object::on_new_document())
         return FALSE;

   
      update_all_views(NULL, 0);

      return TRUE;
   }

   document::~document()
   {
   }


   #ifdef DEBUG
   void document::assert_valid() const
   {
      ::user::object::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::object::dump(dumpcontext);
   }
   #endif //DEBUG



} // namespace userstack



