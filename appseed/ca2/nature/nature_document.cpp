#include "framework.h"


namespace nature
{


   document::document(::ca::applicationsp papp) :
      ca(papp),
      ::ca::data_container_base(papp),
      ::userbase::document(papp)
   {

   }

   bool document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
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
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
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

   void document::data_on_after_change(::ca::signal_object * pobj)
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




   ::view * document::get_nature_view()
   {
      return get_typed_view < ::view > ();
   }


   frame * document::get_nature_frame()
   {
      ::view * pview = get_nature_view();
      return (pview->GetTypedParent < frame >());
   }



   bool document::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      UNREFERENCED_PARAMETER(pcmdui);
      return false;
   }

   bool document::_001OnCommand(id id)
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
         System.appa_set_locale(strLocale, true);
         System.appa_set_schema(strStyle, true);
         System.appa_load_string_table();
      }
      return bOk;
   }


} // namespace nature


