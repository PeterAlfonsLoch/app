#include "StdAfx.h"

namespace webserver
{

namespace kar
{

   body_page::body_page()
   {
      m_params.set_app(get_app());
   }

   bool body_page::has_param(const char * paramName)
   {
//      dprint("$paramName");
      if(m_params[paramName].is_set())
      {
      //   dprint(""-set]"");
         if(strlen(m_params[paramName]) > 0)
         {
            //dprint(""-goodlen}"");
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
   }

} // namespace kar


} // namespace webserver