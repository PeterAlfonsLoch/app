#include "framework.h"

namespace ca
{

   resource::resource()
   {
   }

   resource::~resource()
   {
   }

   bool resource::ReadResource(::ca::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

   bool resource::ReadResource(HINSTANCE hinst, ::ca::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(hinst);
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

} // namespace ca
