#include "framework.h"


CLASS_DECL_C Platform::String ^ m_str(const char * psz)
{
   
   return wstring(psz);

}



CLASS_DECL_C  int MessageBox(void * p, const char * pszMessage, const char * pszTitle, int iFlags)
{
  
   Windows::UI::Popups::MessageDialog ^ merde = ref new Windows::UI::Popups::MessageDialog(pszMessage, pszTitle);
  
   Windows::UI::Popups::UICommand ^ command = merde->ShowAsync()->GetResults();

   command.Close();

   return 1;

}


void WINAPI Sleep(DWORD timeout)
{

   simple_event ev;
   ev.wait
}