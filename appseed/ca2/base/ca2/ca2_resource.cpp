#include "framework.h"

namespace ca2
{

   resource::resource()
   {
   }

   resource::~resource()
   {
   }

   bool resource::ReadResource(::ca2::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

   bool resource::ReadResource(HINSTANCE hinst, ::ca2::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(hinst);
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

} // namespace ca2
