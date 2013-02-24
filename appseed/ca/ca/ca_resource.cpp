#include "framework.h"

namespace gen
{

   resource::resource()
   {
   }

   resource::~resource()
   {
   }

   bool resource::ReadResource(gen::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

   bool resource::ReadResource(HINSTANCE hinst, gen::file & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(hinst);
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

} // namespace gen
