#include "framework.h"


bool CLASS_DECL_AXIS vfxResolveShortcut(string & strTarget,const char * pszSource,sp(::user::interaction) puiMessageParentOptional)
{

   sp(::user::interaction) pui = puiMessageParentOptional;

   wstring wstrFileOut;
   wstring wstrFileIn = ::str::international::utf8_to_unicode(pszSource);

   bool bNativeUnicode = is_windows_native_unicode() != FALSE;


   //   __COM com;
   IShellLinkW* psl;
   wstrFileOut = L"";

   SHFILEINFOW info;

   ZERO(info);

   if((::windows::shell::SHGetFileInfo(wstrFileIn,0,&info,sizeof(info),SHGFI_ATTRIBUTES) == 0) || !(info.dwAttributes & SFGAO_LINK))
   {
      return FALSE;
   }

   HRESULT hr ;
   if(FAILED(hr = CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,IID_IShellLinkW,
      (LPVOID*)&psl)))
   {
      return FALSE;
   }

   IPersistFile *ppf;
   if(SUCCEEDED(psl->QueryInterface(IID_IPersistFile,(LPVOID*)&ppf)))
   {
      if(SUCCEEDED(ppf->Load(wstrFileIn,STGM_READ)))
      {
         /* Resolve the link, this may post UI to find the link */
         if(SUCCEEDED(psl->Resolve(pui == NULL ? NULL : pui->get_handle(),
            SLR_ANY_MATCH | (pui == NULL ? (SLR_NO_UI | (8400 << 16)) : 0))))
         {
            wstrFileOut.alloc(MAX_PATH);
            bool bOk;
            if(SUCCEEDED(psl->GetPath(wstrFileOut,MAX_PATH,NULL,0)))
            {
               bOk = true;
               wstrFileOut.release_buffer();
               strTarget = ::str::international::unicode_to_utf8((LPCWSTR)wstrFileOut);
            }
            else
            {
               bOk = false;
            }
            ppf->Release();
            psl->Release();
            return bOk;
         }
      }
      ppf->Release();
   }
   psl->Release();
   return FALSE;
}
