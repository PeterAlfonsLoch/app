#include "framework.h"


namespace ca2
{

   request_signal::request_signal(sp(base_application) papp, ::ca2::signal * psignal) :
      element(papp),
      signal_details(psignal)
   {
   }


} // namespace ca2
