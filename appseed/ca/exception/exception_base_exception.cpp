#include "StdAfx.h"


void PASCAL base_exception::operator delete(void * pbData)
{
   ::radix::object::operator delete(pbData);
}

void PASCAL base_exception::operator delete(void * pbData,   const char * /* lpszFileName */, int /* nLine */)
{
   operator delete(pbData);
}

base_exception::base_exception(unsigned int uiSkip)
#ifdef WINDOWS
: call_stack(uiSkip)
#endif
{
   // most exceptions are deleted when not needed
   m_ulFlags |= flag_auto_clean;
   m_ulFlags &= ~flag_ready_for_delete;
}

base_exception::base_exception(BOOL bAutoDelete, unsigned int uiSkip)
#ifdef WINDOWS
: call_stack(uiSkip)
#endif
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



void DECLSPEC_NO_RETURN AfxThrowMemoryException()
{
   throw memory_exception();
}

void DECLSPEC_NO_RETURN AfxThrowNotSupportedException()
{
   throw not_supported_exception();
}

void DECLSPEC_NO_RETURN AfxThrowInvalidArgException()
{
   throw invalid_argument_exception();
}


/////////////////////////////////////////////////////////////////////////////

//typedef BOOL (WINAPI *  LPFN_ISWOW64PROCESS )(HANDLE, BOOL *) ;

#ifdef WINDOWS

BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

     if (!IsWow64Process(GetCurrentProcess(),&bIsWow64))
     {
         return FALSE;
     }
    return bIsWow64;
}

#endif
