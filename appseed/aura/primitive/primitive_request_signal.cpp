#include "framework.h"


request_signal::request_signal(sp(::aura::application) papp, class signal * psignal) :
   element(papp),
   signal_details(psignal)
{


}



