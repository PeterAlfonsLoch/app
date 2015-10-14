#include "framework.h"
#include "fiasco_finder.h"




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

      //straFile.add("ucrtbase.dll");
      straFile.add("vcruntime140.dll");
      straFile.add("vcomp140.dll");

   }
   else
   {

      //straFile.add("ucrtbased.dll");
      straFile.add("vcruntime140d.dll");
      straFile.add("vcomp140d.dll");

   }

   return straFile;

}

