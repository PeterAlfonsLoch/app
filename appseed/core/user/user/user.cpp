//#include "framework.h"




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


#ifdef WINDOWS

   CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath)
   {

      return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wstring(strLocalImagePath), SPIF_UPDATEINIFILE) != FALSE;

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


#endif


} // namespace user








