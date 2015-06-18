#pragma once



#include "core/core/core.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "html/html/html.h"
#include "math/math/math_math.h"




#ifdef __SPHERE__DLL
   #define CLASS_DECL_SPHERE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_SPHERE  CLASS_DECL_IMPORT
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


