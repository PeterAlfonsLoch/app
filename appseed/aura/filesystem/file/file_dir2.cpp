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

   return app() / process_platform_dir_name() / app_relative();

}


::file::path dir::userappdata()
{

   return app() / app_relative() / "appdata";
   
}


::file::path dir::app()
{

   return root() / "app";

}


::file::path dir::system()
{

   return root() / "system";

}


::file::path dir::root()
{

   ::file::path str;

#ifdef WINDOWSEX

   str = ::windows::get_known_folder(FOLDERID_RoamingAppData);

   str /= "ca2";

#elif defined(METROWIN)

   str = begin(::Windows::Storage::ApplicationData::Current->LocalFolder->Path);

#elif defined(VSNORD)

   str = ::aura::system::g_p->m_pandroidinitdata->m_pszCacheDir;

#endif

   return str;

}


::file::path dir::app_relative()
{

   string strRelative = dir::element();

   index iFind = strRelative.find(':');

   if (iFind >= 0)
   {

      index iFind1 = strRelative.reverse_find('\\', iFind);

      index iFind2 = strRelative.reverse_find('/', iFind);

      index iStart = MAX(iFind1 + 1, iFind2 + 1);

      strRelative = strRelative.substr(0, iFind - 1) + "_" + strRelative.substr(iStart, iFind - iStart) + strRelative.substr(iFind + 1);

   }

   return strRelative;

}
