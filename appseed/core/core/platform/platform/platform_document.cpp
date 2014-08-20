#include "framework.h"


namespace platform
{


   document::document(sp(::axis::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      html_document(papp),
      form_document(papp)
   {
      
      m_pbergedgedocument = NULL;

   }

   bool document::on_new_document()
   {
      if (!::user::document::on_new_document())
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
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }
   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*void document::Serialize(CArchive& ar)
   {
      if (ar.IsStoring())
      {
         // TODO: add storing code here
      }
      else
      {
         // TODO: add loading code here
      }
   }
   */

   void document::data_on_after_change(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }

   sp(view) document::get_platform_view()
   {

      return get_typed_view < view > ();

   }

   sp(pane_view) document::get_platform_pane_view()
   {

      return get_typed_view < pane_view > ();

   }

   sp(frame) document::get_platform_frame()
   {
      
      sp(pane_view) pview = get_platform_pane_view();
      
      if(pview == NULL)
         return NULL;
      
      sp(frame) pplatformframe = pview->GetTypedParent < frame >();
      
      return pplatformframe;


   }



} // namespace platform



