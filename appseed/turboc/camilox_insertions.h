#pragma once


#include "sphere/sphere.h"

#ifdef __APP_TURBOC_LIBRARY
#define CLASS_DECL_TURBOC  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_TURBOC  CLASS_DECL_IMPORT
#endif

#define WITH_X

namespace turboc
{


   class application;


} // namespace sphere


#undef App
#define App(pcaapp) (pcaapp->cast_app < ::turboc::application > ())


// cax@ca2
typedef int gint;
#define __BEGIN_DECLS
#define __END_DECLS
CLASS_DECL_TURBOC int getch();
