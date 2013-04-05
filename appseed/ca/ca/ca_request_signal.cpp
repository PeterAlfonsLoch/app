#include "framework.h"


namespace ca
{

   request_signal::request_signal(::ca::applicationsp papp, ::ca::signal * psignal) :
      ca(papp),
      signal_object(psignal)
   {
   }


} // namespace ca