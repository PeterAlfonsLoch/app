#include "framework.h"


namespace userstack
{


   document::document(::aura::application * papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {
   }

   bool document::on_new_document()
   {
      if (!::aura::document::on_new_document())
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
      ::aura::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::aura::document::dump(dumpcontext);
   }
   #endif //DEBUG



} // namespace userstack



