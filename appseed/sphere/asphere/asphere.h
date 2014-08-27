#pragma once



#include "core/core/core.h"



#ifdef WINDOWS
#ifdef __SPHERE__DLL
   #define CLASS_DECL_sphere  _declspec(dllexport)
#else
   #define CLASS_DECL_sphere  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_sphere
#endif



namespace sphere
{


   class application;


} // namespace sphere


#undef App
#define App(pcaapp) (pcaapp->cast_app < ::sphere::application > ())


namespace bergedge
{


   class bergedge;


} // namespace bergedge




#include "asphere_application.h"


