#include "framework.h"


simple_exception::simple_exception()
{
   m_bInitialized = FALSE; 
   m_bLoaded = FALSE; 
}

simple_exception::simple_exception(const char * pszMessage)
{
   m_bInitialized = TRUE; 
   m_bLoaded = TRUE; 
   strncpy(m_szMessage, pszMessage, sizeof(m_szMessage));
   m_szMessage[sizeof(m_szMessage) - 1] = '\0';
}

simple_exception::simple_exception(BOOL bAutoDelete)
   : base_exception(bAutoDelete)
{
   m_bInitialized = FALSE; 
   m_bLoaded = FALSE; 
}

simple_exception::~simple_exception()
{

}

void simple_exception::InitString()
{
   m_bInitialized = TRUE;
   throw not_implemented_exception();
//   m_bLoaded = (gen::LoadString(m_nResourceID,
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
