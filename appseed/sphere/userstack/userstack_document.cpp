#include "framework.h"


namespace userstack
{


   document::document(sp(::ca::application) papp) :
      ca(papp),
      ::ca::data_container_base(papp),
      ::userbase::document(papp)
   {
   }

   bool document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;

   
      update_all_views(::null(), 0);

      return TRUE;
   }

   document::~document()
   {
   }


   #ifdef DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //DEBUG



} // namespace userstack



