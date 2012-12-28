#include "framework.h"



namespace ca
{

   system::system()
   {
   }

   system::~system()
   {
   }

   bool system::initialize()
   {
      return true;
   }

   bool system::assert_failed_line(const char * lpszFileName, int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return false;
   }


   bool system::on_assert_failed_line(const char * lpszFileName, int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return true;
   }

   void system::discard_to_factory(::ca::ca * pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

   ::ca::ca * system::clone(::ca::ca * pca)
   {
      UNREFERENCED_PARAMETER(pca);
      return NULL;
   }

   
} // namespace ca