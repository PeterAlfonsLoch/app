#include "framework.h"


namespace ca2
{

   request_signal::request_signal(sp(::ca2::application) papp, ::ca2::signal * psignal) :
      ca2(papp),
      signal_object(psignal)
   {
   }


} // namespace ca2
