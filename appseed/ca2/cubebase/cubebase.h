#pragma once



#include "app/appseed/ca/ca.h"



#ifdef WINDOWS
#ifdef __CA2__DLL
   #define CLASS_DECL_ca2  _declspec(dllexport)
#else
   #define CLASS_DECL_ca2  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_ca2
#endif



namespace cube8
{


   class system;


} // namespace cube8


namespace bergedge
{


   class bergedge;


} // namespace bergedge




#include "cubebase_application.h"


