#include "framework.h"


namespace draw2d_cairo
{


   font::font(sp(::ca2::application) papp) :
   ca2(papp)
   {

   }


   font::~font()
   {

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::ca2::font::dump(dumpcontext);

   }


   void * font::get_os_data() const
   {

      throw interface_only_exception(get_app());

      return NULL;

   }


} // namespace draw2d_cairo





