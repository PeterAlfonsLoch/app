#pragma once


#include "core/core/core.h"


#if defined(_CA2_PROGRAMMING_DLL)
   #define CLASS_DECL_PROGRAMMING  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_PROGRAMMING  CLASS_DECL_IMPORT
#endif




namespace programming
{


   class application;


} // namespace netnode

#undef App
#define App(pcaapp) (pcaapp->cast_app < ::programming::application > ())


#include "app/appseed/programming/dynamic_source/dynamic_source.h"


#include "programming_application.h"