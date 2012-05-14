#include "framework.h"


namespace gen
{

   request_signal::request_signal(::ca::application * papp, gen::signal * psignal) :
      ca(papp),
      signal_object(psignal)
   {
   }


} // namespace gen