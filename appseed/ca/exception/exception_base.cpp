#include "framework.h"


void base_exception::operator delete(void * pbData)
{
   ::ca::object::operator delete(pbData);
}

void base_exception::operator delete(void * pbData,   const char * /* lpszFileName */, int32_t /* nLine */)
{
   operator delete(pbData);
}

base_exception::base_exception(::ca::application * papp, uint32_t uiSkip) :
   ca(papp),
   ::call_stack(papp, uiSkip)
{
   // most exceptions are deleted when not needed
   m_ulFlags |= flag_auto_clean;
   m_ulFlags &= ~flag_ready_for_delete;
}

base_exception::base_exception(::ca::application * papp, bool bAutoDelete, uint32_t uiSkip) :
   ca(papp),
   ::call_stack(papp, uiSkip)
{
   // for exceptions which are not auto-delete (usually)
   if(bAutoDelete)
   {
      m_ulFlags |= flag_auto_clean;
   }
   else
   {
      m_ulFlags &= ~flag_auto_clean;
   }
   m_ulFlags &= ~flag_ready_for_delete;
}

base_exception::~base_exception()
{
}

void base_exception::Delete()
{
   // delete exception if it is auto-deleting
   if(is_set_ca_flag(flag_auto_clean))
   {
      m_ulFlags |= flag_ready_for_delete;
      delete this;
   }
}


bool base_exception::get_error_message(string & str, PUINT pnHelpContext)
{

   if (pnHelpContext != NULL)
      *pnHelpContext = 0;

   str.Empty();

   return false;

}

string base_exception::get_message(PUINT pnHelpContext)
{

   string str;

   if(!get_error_message(str, pnHelpContext))
      return "";

   return str;

}





int32_t base_exception::ReportError(UINT nType /* = MB_OK */,
   const char * pszMessageId /* = NULL */)
{
   string   strErrorMessage;
   int32_t     nDisposition;
   UINT    nHelpContext;

   // nHelpContext should come with the message "<helpcontext id=\"123\" />"

   if (get_error_message(strErrorMessage, &nHelpContext))
      nDisposition = System.simple_message_box(NULL, strErrorMessage, nType);
   else
   {
      if (pszMessageId == 0)
         //pszMessageId = __IDP_NO_ERROR_AVAILABLE;
         pszMessageId = "Mensagem de erro não disponível";
      nDisposition = System.simple_message_box(NULL, pszMessageId, nType);
   }
   return nDisposition;
}


#ifdef WINDOWSEX

bool IsWow64()
{

   WINBOOL bIsWow64 = FALSE;

   if (!IsWow64Process(GetCurrentProcess(),&bIsWow64))
   {
      return FALSE;
   }

   return bIsWow64 != FALSE;

}

#endif
