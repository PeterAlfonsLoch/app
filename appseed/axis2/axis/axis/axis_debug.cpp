#include "framework.h"


CLASS_DECL_AXIS int32_t FUNCTION_DEBUGBOX(const char * pszMessage, const char * pszTitle, int32_t iFlags)
{

   return ::MessageBox(NULL,pszMessage,pszTitle,iFlags);

}


#ifdef DEBUG
void TRACELASTERROR()
{
   sp(::axis::application) m_pbaseapp = get_thread_app();
   string strErrorMessage = ::get_system_error_message(::GetLastError());
   TRACE("Error Message :\n%s\n", strErrorMessage.c_str());
}
#endif


string FormatMessageFromSystem(uint32_t dwError)
{


   return ::get_system_error_message(dwError);


}
