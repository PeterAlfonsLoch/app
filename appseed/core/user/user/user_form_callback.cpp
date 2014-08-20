#include "framework.h"


namespace user
{


   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {

      strsp(form_view)::pair * ppair = m_mapview.PGetFirstAssoc();

      while (ppair != NULL)
      {
         
         ppair->second->DestroyWindow();

         ppair = m_mapview.PGetNextAssoc(ppair);

      }


   }

   void form_callback::on_update(::user::form * pview, sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   bool form_callback::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }

   void form_callback::OnUser123(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
   }

   void form_callback::OnBeforeNavigate2(::html::data * pdata, var & varFile, uint32_t nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);
      UNREFERENCED_PARAMETER(pbCancel);
   }

   void form_callback::_001InitializeFormPreData(::user::form * pform)
   {
      UNREFERENCED_PARAMETER(pform);
   }


} // namespace user

