#include "framework.h"


html_document::html_document(sp(::base::application) papp) :
   element(papp),
   ::data::data_container_base(papp),
   ::user::object(papp)
{


}

bool html_document::on_new_document()
{

   ::database::client::initialize_data_client(Application.simpledb().get_data_server());

   if (!::user::object::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);


   return TRUE;

}

html_document::~html_document()
{
}



#ifdef DEBUG
void html_document::assert_valid() const
{
   ::user::object::assert_valid();
}

void html_document::dump(dump_context & dumpcontext) const
{
   ::user::object::dump(dumpcontext);
}
#endif //DEBUG

/////////////////////////////////////////////////////////////////////////////
// html_document serialization

/*void html_document::Serialize(CArchive& ar)
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

void html_document::data_on_after_change(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void html_document::OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel)
{
   UNREFERENCED_PARAMETER(pdata);
   UNREFERENCED_PARAMETER(varFile);
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(lpszTargetFrameName);
   UNREFERENCED_PARAMETER(baPostedData);
   UNREFERENCED_PARAMETER(lpszHeaders);
   UNREFERENCED_PARAMETER(pbCancel);
}

bool html_document::on_open_document(var varFile)
{

   ::data::lock lock(get_html_data());





   get_html_data()->m_pform = get_typed_view < html_form > ();





   if(get_html_data()->m_pform == NULL)
      return false;


   get_html_data()->m_propset.merge(oprop("html_data_propset").propset());


   if(!get_html_data()->open_document(varFile))
      return FALSE;

   set_path_name(get_html_data()->m_strPathName);
   /*   m_document.m_pbaseapp = get_app();*/

   html_view_update_hint uh;
   uh.m_etype = html_view_update_hint::type_document_complete;
   uh.m_strUrl = varFile;
   update_all_views(NULL, 0, &uh);


   data_set("LastOpenedFile", get_path_name());


   return TRUE;


}

void html_document::soft_reload()
{
   ::data::lock lock(get_html_data());
   string str = get_html_data()->m_strSource;
   //if(m_propset["bReplaceEx1"])
   {
      get_html_data()->m_propertyset.replace_gen(str);
   }
   TRACE0(str);
   get_html_data()->load(str);
   html_view_update_hint uh;
   uh.m_etype = html_view_update_hint::type_document_complete;
   uh.m_strUrl = get_path_name();
   update_all_views(NULL, 0, &uh);
}

::html::data * html_document::get_html_data()
{
   sp(::user::object) pdoc = (this);
   if(pdoc->get_data(this) == NULL)
   {
      set_data(this, get_typed_view < html_form > ()->get_html_data());
      get_html_data()->m_pcallback = this;
      get_html_data()->m_propset["bReplaceEx1"] = true;
   }
   return pdoc->m_spadata.get < ::html::data >();
}

bool html_document::on_simple_update(cmd_ui * pcmdui)
{
   if(pcmdui->m_id == "viewindefaultbrowser")
   {
      pcmdui->Enable();
      return true;
   }
   return false;
}

bool html_document::on_simple_action(id id)
{

   if(id == "viewindefaultbrowser")
   {

      property_set propertyset;

      System.message_box("html_reader\\going_to_open_in_default_browser.xml", propertyset);

#ifndef METROWIN

      simple_shell_launcher launcher(NULL, "open", get_path_name(), NULL, System.dir().name(get_path_name()), SW_SHOWNORMAL);

      launcher.execute();

#endif

      return true;

   }

   return false;

}


bool html_document::open_document(var varFile)
{
   return on_open_document(varFile) != FALSE;
}



