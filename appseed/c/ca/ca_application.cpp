#include "framework.h"


int32_t application::simple_message_box(const char * pszMessage, UINT fuStyle)
{

#if defined(WINDOWSEX)

   return MessageBoxW(NULL, wstring(pszMessage), wstring(m_strAppName), fuStyle);
   //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   //   wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(MACOS) || defined(ANDROID)

   return MessageBox((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

   return MessageBox(m_psystem->m_pui->get_handle(), pszMessage, m_strAppName, fuStyle);

#endif

}


bool application::load_string(string & str, id id)
{
   UNREFERENCED_PARAMETER(id);
   str.Empty();
   return false;
}


sp(element) application::alloc(sp(type) info)
{
   return System.alloc(this, info);
}

sp(element) application::alloc(const  id & idType)
{
   return System.alloc(this, idType);
}







