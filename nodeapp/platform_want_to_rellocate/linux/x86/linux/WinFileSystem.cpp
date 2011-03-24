#include "StdAfx.h"
#include "WinFileSystem.h"


#include "WinFile.h"

WinFileSystem::WinFileSystem(::ca::application * papp) :
   ::ca::ca(papp)
{

}

WinFileSystem::~WinFileSystem()
{

}

bool WinFileSystem::FullPath(string &str, const char * lpszFileIn)
{
   if(gen::str::begins_ci(lpszFileIn, "http://"))
   {
      str = lpszFileIn;
      return true;
   }
   else if(gen::str::begins_ci(lpszFileIn, "https://"))
   {
      str = lpszFileIn;
      return true;
   }
   wstring wstrFileIn;
   gen::international::utf8_to_unicode(wstrFileIn, lpszFileIn);
   wstring wstrFileOut;
   bool b = vfxFullPath(wstrFileOut.GetBufferSetLength(MAX_PATH *2), wstrFileIn) != FALSE;
   wstrFileOut.ReleaseBuffer();
   if(b)
   {
      gen::international::unicode_to_utf8(str, wstrFileOut);
   }
   return b;
}


UINT WinFileSystem::GetFileName(const char * lpszPathName, string & str)
{
   int nMax = 1024 * 2;
   wstring wstrPathName;
   gen::international::utf8_to_unicode(wstrPathName, lpszPathName);
   wstring wstrTitle;
   UINT user = vfxGetFileName(wstrPathName, wstrTitle.GetBufferSetLength(nMax), nMax);
   wstrTitle.ReleaseBuffer();
   str = gen::international::unicode_to_utf8(wstrTitle);
   return user;
}

void WinFileSystem::GetModuleShortFileName(HINSTANCE hInst, string & strShortName)
{
   wstring wstrShortName;
   vfxGetModuleShortFileName(hInst, wstrShortName);
   gen::international::unicode_to_utf8(strShortName, wstrShortName);
}
