#pragma once

#include "include/ca2.h"


#ifdef _VEIEVSERVER_DLL
   #define CLASS_DECL_VEIEVSERVER  _declspec(dllexport)
#else
   #define CLASS_DECL_VEIEVSERVER  _declspec(dllimport)
#endif




namespace veievserver
{
   class application;
} // namespace veievserver

#include "session.h"
#include "socket.h"
#include "socket_thread.h"


#include "service.h"
#include "application.h"