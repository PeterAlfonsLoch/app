#include "framework.h"


namespace draw2d_direct2d
{


   factory_exchange::factory_exchange(::ca2::application * papp) :
      element(papp)
   {

      System.factory().cloneable_large < dib                   >  (System.template type < ::draw2d::dib               > ());
      System.factory().cloneable_large < graphics              >  (System.template type < ::draw2d::graphics          > ());
      System.factory().cloneable_large < graphics_path         >  (System.template type < ::draw2d::path              > ());
      System.factory().cloneable_large < bitmap                >  (System.template type < ::draw2d::bitmap            > ());
      System.factory().cloneable_large < pen                   >  (System.template type < ::draw2d::pen               > ());
      System.factory().cloneable_large < brush                 >  (System.template type < ::draw2d::brush             > ());
      System.factory().cloneable_large < palette               >  (System.template type < ::draw2d::palette           > ());
      System.factory().cloneable_large < region                >  (System.template type < ::draw2d::region            > ());
      System.factory().cloneable_large < font                  >  (System.template type < ::draw2d::font              > ());
      

      ::draw2d_direct2d::dib::s_initialize();

      draw2d_direct2d_initialize();

   }


   factory_exchange::~factory_exchange()
   {

   }


#if defined(METROWIN)

   void factory_exchange::draw2d_direct2d_initialize()
   {

   }

#endif


} // namespace draw2d_direct2d


void ca2_factory_exchange(sp(::application) papp)
{

   draw2d_direct2d::factory_exchange factoryexchange(papp);

}



