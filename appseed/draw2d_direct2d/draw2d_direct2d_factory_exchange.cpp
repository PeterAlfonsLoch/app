#include "framework.h"


namespace draw2d_direct2d
{


   factory_exchange::factory_exchange(::ca2::application * papp) :
      ca2(papp)
   {

      System.factory().cloneable_large < dib                   >  (System.template type_info < ::draw2d::dib               > ());
      System.factory().cloneable_large < graphics              >  (System.template type_info < ::draw2d::graphics          > ());
      System.factory().cloneable_large < graphics_path         >  (System.template type_info < ::draw2d::path              > ());
      System.factory().cloneable_large < bitmap                >  (System.template type_info < ::draw2d::bitmap            > ());
      System.factory().cloneable_large < pen                   >  (System.template type_info < ::draw2d::pen               > ());
      System.factory().cloneable_large < brush                 >  (System.template type_info < ::draw2d::brush             > ());
      System.factory().cloneable_large < palette               >  (System.template type_info < ::draw2d::palette           > ());
      System.factory().cloneable_large < region                >  (System.template type_info < ::draw2d::region            > ());
      System.factory().cloneable_large < font                  >  (System.template type_info < ::draw2d::font              > ());
      

      ::draw2d_direct2d::dib::s_initialize();

      draw2d_direct2d_initialize();

   }


   factory_exchange::~factory_exchange()
   {
   }


} // namespace draw2d_direct2d



void ca2_factory_exchange(::ca2::application * papp)
{
   draw2d_direct2d::factory_exchange factoryexchange(papp);
}



