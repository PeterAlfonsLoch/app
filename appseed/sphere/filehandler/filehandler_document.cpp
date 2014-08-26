#include "framework.h"


namespace filehandler
{


   document::document(sp(::aura::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      html_document(papp)
   {
   }

   bool document::on_new_document()
   {
      if (!::user::document::on_new_document())
         return FALSE;

//      if(!get_data()->on_open_document("rtp://10.10.100.97:19847"))
   //    {
      //     delete_contents();
      //   return FALSE;
      //}

      //update_all_views(NULL, 19847);

      return TRUE;
   }

   bool document::on_open_document(var varFile) 
   {
      return TRUE;
   }


   document::~document()
   {
   }



   #ifdef DEBUG
   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }
   #endif //DEBUG


} // namespace filehandler





