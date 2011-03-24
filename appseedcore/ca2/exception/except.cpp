#include "StdAfx.h"
#include "sal.h"


void PASCAL base_exception::operator delete(void * pbData)
{
   ::radix::object::operator delete(pbData);
}

void PASCAL base_exception::operator delete(void * pbData,   const char * /* lpszFileName */, int /* nLine */)
{
   operator delete(pbData);
}

base_exception::base_exception(unsigned int uiSkip) :
   call_stack(uiSkip)
{
   // most exceptions are deleted when not needed
   m_ulFlags |= flag_auto_clean;
   m_ulFlags &= ~flag_ready_for_delete;
}

base_exception::base_exception(BOOL bAutoDelete, unsigned int uiSkip) :
   call_stack(uiSkip)
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

void base_exception::Delete()
{
   // delete exception if it is auto-deleting
   if(is_set(flag_auto_clean) > 0)
   {
      m_ulFlags |= flag_ready_for_delete;
      delete this;
   }
}

BOOL base_exception::GetErrorMessage(string & str,   PUINT pnHelpContext /* = NULL */ )
{
   if (pnHelpContext != NULL)
      *pnHelpContext = 0;

   str.Empty();

   return FALSE;
}


int base_exception::ReportError(UINT nType /* = MB_OK */,
   const char * pszMessageId /* = NULL */)
{
   string   strErrorMessage;
   int     nDisposition;
   UINT    nHelpContext;

   // nHelpContext should come with the message "<helpcontext id=\"123\" />"

   if (GetErrorMessage(strErrorMessage, &nHelpContext))
      nDisposition = System.simple_message_box(NULL, strErrorMessage, nType);
   else
   {
      if (pszMessageId == 0)
         //pszMessageId = AFX_IDP_NO_ERROR_AVAILABLE;
         pszMessageId = "Mensagem de erro não disponível";
      nDisposition = System.simple_message_box(NULL, pszMessageId, nType);
   }
   return nDisposition;
}



// IMPLEMENT_DYNAMIC(base_exception, ::radix::object)

// IMPLEMENT_DYNAMIC(memory_exception, base_exception)
//memory_exception _simpleMemoryException(FALSE, AFX_IDS_MEMORY_EXCEPTION);

// IMPLEMENT_DYNAMIC(CNotSupportedException, base_exception)
//CNotSupportedException _simpleNotSupportedException(FALSE, AFX_IDS_NOT_SUPPORTED_EXCEPTION);

// IMPLEMENT_DYNAMIC(invalid_argument_exception, base_exception)
//invalid_argument_exception _simpleInvalidArgException(FALSE, AFX_IDS_INVALID_ARG_EXCEPTION);

/////////////////////////////////////////////////////////////////////////////
// Standard exceptions


void simple_exception::InitString()
{
   m_bInitialized = TRUE;
   throw not_implemented_exception();
//   m_bLoaded = (AfxLoadString(m_nResourceID,
//      m_szMessage, _countof(m_szMessage)) != 0);

}

BOOL simple_exception::GetErrorMessage(string & str, PUINT pnHelpContext)
{

   if (pnHelpContext != NULL)
      *pnHelpContext = 0;

   // if we didn't load our string (eg, we're a console cast)
   // return a null string and FALSE

   if (!m_bInitialized)
      const_cast<simple_exception*>(this)->InitString();

   if (m_bLoaded)
      str = m_szMessage;
   else
      str.Empty();

   return m_bLoaded;
}

void __declspec(noreturn) AfxThrowMemoryException()
{
   throw memory_exception();
}

void __declspec(noreturn) AfxThrowNotSupportedException()
{
   throw not_supported_exception();
}

void __declspec(noreturn) AfxThrowInvalidArgException()
{
   throw invalid_argument_exception();
}


/////////////////////////////////////////////////////////////////////////////

//typedef BOOL (WINAPI *  LPFN_ISWOW64PROCESS )(HANDLE, BOOL *) ;

BOOL IsWow64()
{
#if core_level_1 || core_level_2
   return FALSE;
#else
    BOOL bIsWow64 = FALSE;

     if (!IsWow64Process(GetCurrentProcess(),&bIsWow64))
     {
         return FALSE;
     }
    return bIsWow64;
#endif
}
