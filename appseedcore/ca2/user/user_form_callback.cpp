#include "StdAfx.h"

namespace user
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   void form_callback::on_update(::user::form * pview, ::view * pSender, LPARAM lHint, ::radix::object* phint)
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

   void form_callback::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(lpszUrl);
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