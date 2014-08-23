#include "framework.h"


namespace draw2d_direct2d
{


   factory_exchange::factory_exchange(sp(::aura::application) papp) :
      element(papp)
   {

      init_draw2d_direct2_mutex(papp);

      System.factory().cloneable_large < dib                   >  (System.type_info < ::draw2d::dib               > ());
      System.factory().cloneable_large < graphics              >  (System.type_info < ::draw2d::graphics          > ());
      System.factory().cloneable_large < graphics_path         >  (System.type_info < ::draw2d::path              > ());
      System.factory().cloneable_large < bitmap                >  (System.type_info < ::draw2d::bitmap            > ());
      System.factory().cloneable_large < pen                   >  (System.type_info < ::draw2d::pen               > ());
      System.factory().cloneable_large < brush                 >  (System.type_info < ::draw2d::brush             > ());
      System.factory().cloneable_large < palette               >  (System.type_info < ::draw2d::palette           > ());
      System.factory().cloneable_large < region                >  (System.type_info < ::draw2d::region            > ());
      System.factory().cloneable_large < font                  >  (System.type_info < ::draw2d::font              > ());
      System.factory().cloneable_large < printer               >  (System.type_info < ::user::printer             >());
      

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



void draw2d_factory_exchange(sp(::aura::application) papp)
{

   draw2d_direct2d::factory_exchange factoryexchange(papp);

}


void ca2_factory_exchange(sp(::aura::application) papp)
{

   draw2d_direct2d::factory_exchange factoryexchange(papp);

}



