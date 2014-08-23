#include "framework.h"


namespace nature
{


   document::document(sp(::aura::application) papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::user::document(papp)
   {

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

   bool document::on_open_document(var varFile)
   {
      string str = Application.file().as_string(varFile);
      if(str.is_empty())
      {
         System.sync_load_url(str, varFile, &ApplicationUser);
      }
      update_all_views(NULL, 123);
      return TRUE;
   }




   sp(::user::impact) document::get_nature_view()
   {
      return get_typed_view < ::user::impact > ();
   }


   sp(frame) document::get_nature_frame()
   {
      sp(::user::impact) pview = get_nature_view();
      return (pview->GetTypedParent < frame >());
   }



   bool document::on_simple_update(cmd_ui * pcmdui)
   {
      UNREFERENCED_PARAMETER(pcmdui);
      return false;
   }

   bool document::on_simple_action(id id)
   {
      bool bOk;
      string strLocale = "se";
      if(id == unitext("Svenska"))
      {
         strLocale = "se";
         bOk = true;
      }
      else if(id == unitext("International English"))
      {
         strLocale = "en";
         bOk = true;
      }
      else if(id == unitext("Português do Brasil"))
      {
         strLocale = "pt-br";
         bOk = true;
      }
      else if(id == unitext("日本語"))
      {
         strLocale = "jp";
         bOk = true;
      }
      else
      {
         bOk = false;
      }
      string strStyle = strLocale;
      if(bOk)
      {
         System.appa_set_locale(strLocale, ::action::source::user());
         System.appa_set_schema(strStyle, ::action::source::user());
         System.appa_load_string_table();
      }
      return bOk;
   }


} // namespace nature


