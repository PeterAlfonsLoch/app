#include "framework.h"

#ifndef CUBE
BOOL WINAPI DllMain(HINSTANCE hInstance,DWORD dwReason,LPVOID lpReserved)
{

   //Sleep(30000);

   //   ASSERT(FALSE);

   xxdebug_box("draw2d_opengl.dll DllMain (0)","box",MB_OK);

   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   //openssl_DllMain(hInstance, dwReason, lpReserved);


   if(dwReason == DLL_PROCESS_ATTACH)
   {




   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {



   }

   return 1;   // ok

}

#endif







//CLASS_DECL_AURA int GetEncoderClsid(const WCHAR* format,CLSID* pClsid)
//{
//   UINT  num = 0;          // number of image encoders
//   UINT  size = 0;         // size of the image encoder array in bytes
//
//   plusplus::ImageCodecInfo* pImageCodecInfo = NULL;
//
//   plusplus::GetImageEncodersSize(&num,&size);
//   if(size == 0)
//      return -1;  // Failure
//
//   pImageCodecInfo = (plusplus::ImageCodecInfo*)(malloc(size));
//   if(pImageCodecInfo == NULL)
//      return -1;  // Failure
//
//   GetImageEncoders(num,size,pImageCodecInfo);
//
//   for(UINT j = 0; j < num; ++j)
//   {
//      if(wcscmp(pImageCodecInfo[j].MimeType,format) == 0)
//      {
//         *pClsid = pImageCodecInfo[j].Clsid;
//         free(pImageCodecInfo);
//         return j;  // Success
//      }
//   }
//
//   free(pImageCodecInfo);
//   return -1;  // Failure
//}




#ifdef WINDOWS


#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")


#endif