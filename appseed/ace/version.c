#include "ace.h"


CLASS_DECL_ACE int _ca_is_basis()
{
#if CA2_PLATFORM_VERSION == CA2_BASIS
   return TRUE;
#else
   return FALSE;
#endif
}

CLASS_DECL_ACE int _ca_is_stage()
{
#if CA2_PLATFORM_VERSION == CA2_STAGE
   return TRUE;
#else
   return FALSE;
#endif
}


BOOL get_version_ex_a(LPOSVERSIONINFOA lpVersionInformation)
{

#if defined(_WIN32) || defined(_UWP)

   /* Windows 10 Version Info */
   if ((lpVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA)) ||
      (lpVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA)))
   {
      lpVersionInformation->dwMajorVersion = 10;
      lpVersionInformation->dwMinorVersion = 0;
      lpVersionInformation->dwBuildNumber = 0;
      lpVersionInformation->dwPlatformId = VER_PLATFORM_WIN32_NT;
      ZeroMemory(lpVersionInformation->szCSDVersion, sizeof(lpVersionInformation->szCSDVersion));

      if (lpVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA))
      {
         LPOSVERSIONINFOEXA lpVersionInformationEx = (LPOSVERSIONINFOEXA)lpVersionInformation;
         lpVersionInformationEx->wServicePackMajor = 0;
         lpVersionInformationEx->wServicePackMinor = 0;
         lpVersionInformationEx->wSuiteMask = 0;
         lpVersionInformationEx->wProductType = VER_NT_WORKSTATION;
         lpVersionInformationEx->wReserved = 0;
      }

      return TRUE;
   }

#else

   /* Windows 7 SP1 Version Info */
   if ((lpVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA)) ||
      (lpVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA)))
   {
      lpVersionInformation->dwMajorVersion = 6;
      lpVersionInformation->dwMinorVersion = 1;
      lpVersionInformation->dwBuildNumber = 7601;
      lpVersionInformation->dwPlatformId = VER_PLATFORM_WIN32_NT;
      ZeroMemory(lpVersionInformation->szCSDVersion, sizeof(lpVersionInformation->szCSDVersion));

      if (lpVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA))
      {
         LPOSVERSIONINFOEXA lpVersionInformationEx = (LPOSVERSIONINFOEXA)lpVersionInformation;
         lpVersionInformationEx->wServicePackMajor = 1;
         lpVersionInformationEx->wServicePackMinor = 0;
         lpVersionInformationEx->wSuiteMask = 0;
         lpVersionInformationEx->wProductType = VER_NT_WORKSTATION;
         lpVersionInformationEx->wReserved = 0;
      }

      return TRUE;
   }


#endif

   return FALSE;

}

