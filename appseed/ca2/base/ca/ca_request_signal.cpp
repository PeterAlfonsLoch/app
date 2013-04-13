#include "framework.h"


namespace ca
{

   request_signal::request_signal(sp(::ca::application) papp, ::ca::signal * psignal) :
      ca(papp),
      signal_object(psignal)
   {
   }


} // namespace ca