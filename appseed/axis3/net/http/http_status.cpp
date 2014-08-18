#include "framework.h"


namespace http
{

   bool succeeded(e_status estatus)
   {

      switch (estatus)
      {
      case status_ok:
      case status_unchanged:
         return true;
      default:
         break;
      }

      return false;

   }

   bool status_succeeded(int64_t i)
   {

      return succeeded((e_status) i);

   }


   bool failed(e_status estatus)
   {
      
      return !succeeded(estatus);

   }


   bool status_failed(int64_t i)
   {

      return !status_succeeded(i);

   }

} // namespace http
















