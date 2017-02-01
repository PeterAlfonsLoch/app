//#include "framework.h"


#ifdef MACOS

long long mm_get_user_wallpaper(char *** ppp);

CLASS_DECL_CORE stringa macos_get_user_wallpaper()
{

   stringa stra;

   char ** ppsz = NULL;

   long long ll = mm_get_user_wallpaper(&ppsz);

   if(ppsz == NULL)
   {

      return stra;

   }

   for(index i = 0; i < ll; i++)
   {

      if(ppsz[i] != NULL)
      {

         stra.add(ppsz[i]);

         ::str::begins_eat_ci(stra.last(), "file://");

         //free(ppsz[i]);

      }
      else
      {

         stra.add("");

      }

   }

   //free(ppsz);

   return stra;

}

#endif

namespace user
{


   CLASS_DECL_CORE sp(::user::interaction) create_virtual_window(::aura::application * papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
                                                             const RECT & rect, sp(::user::interaction) puiParent, id id, HINSTANCE hInstance, LPVOID lpParam);


   CLASS_DECL_CORE sp(::user::interaction) create_virtual_window(::aura::application * papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
      const RECT & rect, sp(::user::interaction) puiParent, id id, HINSTANCE hInstance, LPVOID lpParam)
   {
      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(lpClassName);
      UNREFERENCED_PARAMETER(lpWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(hInstance);
      UNREFERENCED_PARAMETER(lpParam);
      sp(::user::interaction) pui = new ::user::interaction(papp);
      if(pui->create_window(rect, puiParent, id))
      {
         return pui;
      }
      pui.release();
      return NULL;
   }


#ifdef WINDOWSEX

   CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath)
   {

      return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wstring(strLocalImagePath), SPIF_UPDATEINIFILE) != FALSE;

   }


   CLASS_DECL_CORE stringa get_wallpaper()
   {

      wchar_t sz[MAX_PATH * 8];

      if(!SystemParametersInfoW(SPI_GETDESKWALLPAPER, MAX_PATH * 8, sz, 0))
      {

         return "";

      }

      return stringa(sz);

   }


#elif defined(LINUX)

   CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath)
   {

      // wall-changer sourceforge.net contribution

      switch(get_edesktop())
      {

         case desktop_gnome:
         case desktop_unity_gnome:

            return gsettings_set("org.gnome.desktop.background", "picture-uri", "file://" + strLocalImagePath);

         case desktop_mate:

            return gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

         case desktop_lxde:

            call_async("pcmanfm", "-w " + strLocalImagePath, NULL, SW_HIDE, false);

            break;

         case desktop_xfce:
            {
//        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << "/backdrop" << "-l").split("\n")){
  //          if(entry.contains("image-path") || entry.contains("last-image")){
    //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << entry << "-s" << image);
      //      }
        //}

            }

            //break;

         default:

            output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
            return false;

      }

      return true;

   }


   CLASS_DECL_CORE stringa get_wallpaper()
   {

      char sz[MAX_PATH * 8];

      ZERO(sz);

      // wall-changer sourceforge.net contribution

      switch(get_edesktop())
      {

         case desktop_gnome:
         case desktop_unity_gnome:

            gsettings_get(sz, sizeof(sz), "org.gnome.desktop.background", "picture-uri");

            break;

         case desktop_mate:

            gsettings_get(sz, sizeof(sz), "org.mate.background", "picture-filename");

            break;

         case desktop_lxde:

            //call_async("pcmanfm", "-w " + strLocalImagePath, NULL, SW_HIDE, false);

            break;

         case desktop_xfce:
            {
//        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << "/backdrop" << "-l").split("\n")){
  //          if(entry.contains("image-path") || entry.contains("last-image")){
    //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << entry << "-s" << image);
      //      }
        //}

            }

            //break;

         default:

            output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
            //return "";

      }

      string str(sz);

      ::str::begins_eat_ci(str, "file://");

      return str;

   }


#elif defined(APPLE_IOS)

   CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath)
   {

      // Someday we will be together...
      // What do you mean...
      // Cold Water...

      return false;

   }

#elif defined(ANDROID)

   CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath)
   {

      return ::aura::system::g_p->android_set_user_wallpaper(strLocalImagePath);

   }

#elif defined(METROWIN)

   CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath)
   {

      // Someday we will be together...
      // What do you mean...
      // Cold Water...

      return false;

   }

#else

   CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath)
   {

      return macos_set_user_wallpaper(strLocalImagePath);

   }

   CLASS_DECL_CORE stringa get_wallpaper()
   {

      return macos_get_user_wallpaper();

   }

#endif


} // namespace user








