#include "StdAfx.h"

namespace veriview
{

   main_document::main_document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
      m_paddressview    = NULL;
      m_ppaneview       = NULL;
   }

   main_document::~main_document()
   {
   }

   bool main_document::on_open_document(var varFile)
   {
      UNREFERENCED_PARAMETER(varFile);
      //if(!document::on_open_document(lpcszPathName))
        // return FALSE;

      /*pane_view_update_hint uh;

      uh.set_type(pane_view_update_hint::TypeOpenDocument);

      update_all_views(NULL, 0, &uh);*/


      return true;
   }

   string main_document::get_url()
   {
      if(m_ppaneview == NULL)
         return "";
      html_document * pdoc = m_ppaneview->get_view_html_document();
      if(pdoc == NULL)
         return "";
      return pdoc->get_path_name();
   }

} // namespace veriview
