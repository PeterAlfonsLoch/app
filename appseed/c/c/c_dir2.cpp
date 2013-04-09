#include "framework.h"
#ifdef WINDOWS
#include <Shlobj.h>
#endif


vsstring dir::afterca2()
{
   return ca();
}

vsstring dir::appdata(const char * lpcsz)
{

   vsstring str;


#ifdef METROWIN

   vsstring buf;

   buf = "C:\\ProgramData";
   
   str = path(buf, "ca2");
   
   //_ca_free(buf, 0);

#elif defined(WIN32)
   
   char * buf = (char *) _ca_alloc(4096);
   
   memset_dup(buf, 0, sizeof(buf));
   
   SHGetSpecialFolderPath(
      ::null(),
      buf,
      CSIDL_COMMON_APPDATA,
      FALSE);
   
   str = path(buf, "ca2");
   
   _ca_free(buf, 0);

#endif
   
   vsstring strCa2 = dir::ca();
   
   index iFind = strCa2.find(':');
   
   if(iFind >= 0)
   {
      
      index iFind1 = strCa2.rfind('\\', iFind);
      
      index iFind2 = strCa2.rfind('/', iFind);
      
      index iStart = max(iFind1 + 1, iFind2 + 1);
      
      strCa2 = strCa2.substr(0, iFind - 1) + "_" + strCa2.substr(iStart, iFind - iStart) + strCa2.substr(iFind + 1);

   }
   
   str = path(str, strCa2);
   
   return path(str, lpcsz);

}






vsstring dir::userappdata(const char * lpcsz)
{

   vsstring str;

#ifdef WINDOWSEX
   
   wchar_t * buf = ::null();
   
   SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, ::null(), &buf);

   char * psz = utf16_to_8(buf);

   str = path(psz, "ca2");

   ca2_free(psz);
   
   CoTaskMemFree(buf);

#elif defined(METROWIN)

   str = begin(::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

#endif
   
   vsstring strCa2 = dir::ca();
   
   index iFind = strCa2.find(':');
   
   if(iFind >= 0)
   {
      
      index iFind1 = strCa2.rfind('\\', iFind);
      
      index iFind2 = strCa2.rfind('/', iFind);
      
      index iStart = max(iFind1 + 1, iFind2 + 1);
      
      strCa2 = strCa2.substr(0, iFind - 1) + "_" + strCa2.substr(iStart, iFind - iStart) + strCa2.substr(iFind + 1);

   }
   
   str = path(str, strCa2);
   
   return path(str, lpcsz);

}
