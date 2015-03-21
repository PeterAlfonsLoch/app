

stringa install_get_plugin_base_library_list(const string & strVersion)
{

   stringa straFile;

   straFile.add("app.install.exe");
   straFile.add("aqua.dll");
   straFile.add("aura.dll");
   straFile.add("aurasqlite.dll");
   straFile.add("axis.dll");
   straFile.add("axisbzip2.dll");
   straFile.add("axiscrypto.dll");
   //straFile.add("axisfreeimage.dll");
   //straFile.add("axisfreetype.dll");
   straFile.add("axisidn.dll");
   straFile.add("axisopenssl.dll");
   straFile.add("axiszlib.dll");
   straFile.add("axis.dll");
   straFile.add("base.dll");
   straFile.add("draw2d_gdiplus.dll");

   if(strVersion == "stage")
   {

      straFile.add("msvcp120.dll");
      straFile.add("msvcr120.dll");
      straFile.add("vcomp120.dll");

   }
   else
   {

      straFile.add("msvcp120d.dll");
      straFile.add("msvcr120d.dll");
      straFile.add("vcomp120d.dll");

   }

   return straFile;

}

