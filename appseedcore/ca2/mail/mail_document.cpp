#include "StdAfx.h"

namespace mail
{

   document::document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
      m_paccount           = NULL;
      m_pholderMailList    = NULL;
   }

   document::~document()
   {
   }


   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::document::dump(dumpcontext);
   }
   #endif //_DEBUG


   void document::data_on_after_change(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void document::set_account(account * pacc)
   {
      m_paccount = pacc;
      update_all_views(NULL, hint_email_changed, NULL);
   }

   void document::open_email(const char * pszEmailId)
   {
      m_strOpenEmailId = pszEmailId;
      update_all_views(NULL, hint_open_email, NULL);
   }

} // namespace mail