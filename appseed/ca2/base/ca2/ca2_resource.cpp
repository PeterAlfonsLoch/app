#include "framework.h"

namespace ca2
{

   resource::resource()
   {
   }

   resource::~resource()
   {
   }

   bool resource::ReadResource(::file::binary_buffer & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

   bool resource::ReadResource(HINSTANCE hinst, ::file::binary_buffer & file, UINT nID, const char * lpcszType)
   {
      UNREFERENCED_PARAMETER(hinst);
      UNREFERENCED_PARAMETER(file);
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      return false;
   }

} // namespace ca2
