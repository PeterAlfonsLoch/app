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


} // namespace turboc


#undef App
#define App(pcaapp) (pcaapp->cast_app < ::turboc::application > ())


// cax@ca2
typedef int gint;
#define __BEGIN_DECLS
#define __END_DECLS
CLASS_DECL_TURBOC int getch();
CLASS_DECL_TURBOC void ungetch(int c);

namespace turboc
{



class CLASS_DECL_TURBOC context :
   virtual public ::object
{
public:



   ::draw2d::dib_sp           m_dib;

   context(::aura::application * papp);
   virtual ~context();

   bool gok();

   void erase();

};

CLASS_DECL_TURBOC void set_context(::turboc::context * pcontext);

} // namespace turboc

CLASS_DECL_TURBOC ::turboc::context & get_turboc_context();
CLASS_DECL_TURBOC ::turboc::application & get_turboc_application();
CLASS_DECL_TURBOC ::console::application & get_console_application();

inline ::turboc::context & tc()
{
   return get_turboc_context();
}