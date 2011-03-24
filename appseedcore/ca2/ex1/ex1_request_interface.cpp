#include "StdAfx.h"


namespace ex1
{

   void request_interface::request(var & varFile, var & varQuery)
   {
      on_request(varFile, varQuery);
   }

   void request_interface::on_request(var & varFile, var & varQuery)
   {
      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(varQuery);
   }

} // namespace ex1