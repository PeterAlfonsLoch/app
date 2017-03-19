#include "framework.h" // from "aura/net/net_sockets.h"



thread_int_ptr < int_ptr > t_bSockets;

CLASS_DECL_AURA void thread_touch_sockets()
{

   t_bSockets = true;

}


CLASS_DECL_AURA int thread_has_sockets()
{

   return (int) (int_ptr) t_bSockets;

}
