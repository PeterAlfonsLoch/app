#include "StdAfx.h"


namespace alatel
{

   
   main_view::main_view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
   }

   main_view::~main_view()
   {
   }


#ifdef _DEBUG
   void main_view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void main_view::dump(dump_context& dc) const
   {
	   ::userbase::view::dump(dc);
   }
#endif //_DEBUG

   void main_view:: _001OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }


} // namespace alatel


