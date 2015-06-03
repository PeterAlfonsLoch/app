//#include "framework.h"
#ifdef WINDOWS
//#include <Shlobj.h>
#endif


::file::path dir::afterca2()
{

   return element();

}


::file::path dir::appdata()
{

   ::file::path str;


#ifdef METROWIN

   string buf;

   buf = "C:\\ProgramData";
   
   str = path(buf, "ca2");
   
   //memory_free_dbg(buf, 0);

#elif defined(WIN32)
   
   SHGetSpecialFolderPath(NULL, str, CSIDL_COMMON_APPDATA, FALSE);
   
   str /= "ca2";

#endif
   
   string strCa2 = dir::element();
   
   index iFind = strCa2.find(':');
   
   if(iFind >= 0)
   {
      
      index iFind1 = strCa2.reverse_find('\\', iFind);
      
      index iFind2 = strCa2.reverse_find('/', iFind);
      
      index iStart = MAX(iFind1 + 1, iFind2 + 1);
      
      strCa2 = strCa2.substr(0, iFind - 1) + "_" + strCa2.substr(iStart, iFind - iStart) + strCa2.substr(iFind + 1);

   }

   str /= process_platform_dir_name();
   
   return str / strCa2;

}






::file::path dir::userappdata()
{

   ::file::path str;

#ifdef WINDOWSEX


   ::SHGetSpecialFolderPath(NULL, str, CSIDL_PROFILE, TRUE);

   str /= "ca2";


#elif defined(METROWIN)


   str = begin(::Windows::Storage::ApplicationData::Current->LocalFolder->Path);


#endif
   
   string strCa2 = dir::element();
   
   index iFind = strCa2.find(':');
   
   if(iFind >= 0)
   {
      
      index iFind1 = strCa2.reverse_find('\\', iFind);
      
      index iFind2 = strCa2.reverse_find('/', iFind);
      
      index iStart = MAX(iFind1 + 1, iFind2 + 1);
      
      strCa2 = strCa2.substr(0, iFind - 1) + "_" + strCa2.substr(iStart, iFind - iStart) + strCa2.substr(iFind + 1);

   }
   
   str /= strCa2;

   return str/ "appdata";
   
}

