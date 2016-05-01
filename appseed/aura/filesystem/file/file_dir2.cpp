//#include "framework.h"


#ifdef WINDOWSEX


namespace windows
{


   ::file::path get_known_folder(REFKNOWNFOLDERID kfid);


} // namespace windows


#endif


::file::path dir::afterca2()
{

   return element();

}


::file::path dir::appdata()
{

   ::file::path str;


#ifdef METROWIN

   str = ::file::path(::file::path(::Windows::Storage::ApplicationData::Current->LocalFolder->Path));

   
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

   str = ::windows::get_known_folder(FOLDERID_RoamingAppData);

   str /= "ca2";

#elif defined(METROWIN)

   str = begin(::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

#endif
   
   str /= "app";

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


::file::path dir::system()
{

   ::file::path str;

#ifdef WINDOWSEX

   str = ::windows::get_known_folder(FOLDERID_RoamingAppData);

   str /= "ca2";

#elif defined(METROWIN)

   str = begin(::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

#endif

   str /= "system";

   return str;

}