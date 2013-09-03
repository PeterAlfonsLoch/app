#include "framework.h"


namespace draw2d_cairo
{


   factory_exchange::factory_exchange(sp(base_application) papp) :
      element(papp)
   {

      System.factory().cloneable_large < dib                   >  (System. type < ::draw2d::dib                 > ());
      System.factory().cloneable_large < graphics              >  (System. type < ::draw2d::graphics            > ());
      System.factory().cloneable_large < bitmap                >  (System. type < ::draw2d::bitmap              > ());
      System.factory().cloneable_large < pen                   >  (System. type < ::draw2d::pen                 > ());
      System.factory().cloneable_large < brush                 >  (System. type < ::draw2d::brush               > ());
      System.factory().cloneable_large < palette               >  (System. type < ::draw2d::palette             > ());
      System.factory().cloneable_large < region                >  (System. type < ::draw2d::region              > ());
      System.factory().cloneable_large < font                  >  (System. type < ::draw2d::font                > ());
      System.factory().cloneable_large < path                  >  (System. type < ::draw2d::path                > ());

      ::draw2d_cairo::dib::s_initialize();

   }


   factory_exchange::~factory_exchange()
   {

   }


} // namespace win


extern "C"
void ca2_factory_exchange(sp(base_application) papp)
{
   draw2d_cairo::factory_exchange factoryexchange(papp);
}


