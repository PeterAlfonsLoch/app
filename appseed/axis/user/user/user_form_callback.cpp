//#include "framework.h"


namespace user
{


   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {

      strsp(::user::form_window)::pair * ppair = m_mapform.PGetFirstAssoc();

      while(ppair != NULL)
      {

         ppair->m_element2->DestroyWindow();

         ppair = m_mapform.PGetNextAssoc(ppair);

      }


   }

   void form_callback::on_update(::user::impact * pform,sp(::user::impact) pSender,LPARAM lHint,object* phint)
   {
      UNREFERENCED_PARAMETER(pform);
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   bool form_callback::BaseOnControlEvent(::user::form_window * pview,::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }

   void form_callback::OnUser123(WPARAM wparam,LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
   }

   void form_callback::OnBeforeNavigate2(::html::data * pdata,var & varFile,uint32_t nFlags,const char * lpszTargetFrameName,byte_array& baPostedData,const char * lpszHeaders,bool* pbCancel)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);
      UNREFERENCED_PARAMETER(pbCancel);
   }

   void form_callback::_001InitializeFormPreData(::user::form_window * pform)
   {
      UNREFERENCED_PARAMETER(pform);
   }


   form_view * form_callback::get_form_view(const string & strId)
   {

      return m_mapform[strId]->m_pformview;

   }

   ::user::document * form_callback::get_form_document(const string & strId)
   {

      auto passoc = m_mapform.PLookup(strId);

      if(passoc == NULL)
         return NULL;

      sp(::user::impact) pview = passoc->m_element2;

      if(pview.is_null())
         return NULL;

      return pview->get_document();

   }



} // namespace user

