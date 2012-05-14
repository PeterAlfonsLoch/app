#include "framework.h"

namespace ex1
{

   resource::resource()
   {
   }

   resource::~resource()
   {
   }

   bool resource::ReadResource(ex1::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

   bool resource::ReadResource(HINSTANCE hinst, ex1::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(hinst);
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

} // namespace ex1
