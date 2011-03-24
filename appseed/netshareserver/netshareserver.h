#pragma once

#include "include/cube.h"


#ifdef _NETSHARESERVER_DLL
   #define CLASS_DECL_NETSHARESERVER  _declspec(dllexport)
#else
   #define CLASS_DECL_NETSHARESERVER  _declspec(dllimport)
#endif




namespace netshareserver
{
   class application;
} // namespace netshareserver

#include "session.h"
#include "socket.h"
#include "socket_thread.h"


#include "service.h"
#include "application.h"