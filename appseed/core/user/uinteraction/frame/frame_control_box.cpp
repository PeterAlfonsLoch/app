#include "framework.h"


namespace uinteraction
{


   namespace frame
   {


      control_box::control_box(sp(base_application) papp) :
         element(papp),
         ::user::interaction(papp)
      {

      }


      control_box::~control_box()
      {

      }


   } // namespace frame


} // namespace uinteraction




