#include "framework.h"


namespace bergedge
{


   document::document(sp(::base::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::user::object(papp)
   {
      m_pplatformdocument = NULL;
      m_pnaturedocument = NULL;
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



   sp(::bergedge::view) document::get_bergedge_view()
   {
      return get_typed_view < ::bergedge::view > ();
   }

   void document::set_platform(sp(::platform::document) pdoc)
   {
      m_pplatformdocument = pdoc;
      //platform_frame * pframe = pdoc->get_platform_frame();
      //pframe->set_parent(get_bergedge_view());
      //pframe->ModifyStyle(0, WS_CHILD);
      //pframe->WfiRestore();
      //pframe->SetWindowPos(0, 0, 0, 200, 200, SWP_SHOWWINDOW);
   }

   void document::set_nature(sp(::nature::document) pdoc)
   {
      m_pnaturedocument = pdoc;
      //nature_frame * pframe = pdoc->get_nature_frame();
      //pframe->set_parent(get_bergedge_view());
      //pframe->ModifyStyle(0, WS_CHILD);
      //pframe->SetWindowPos(0, 200, 200, 400, 400, SWP_SHOWWINDOW);
   }



} // namespace bergedge



