#include "framework.h"


namespace filemanager
{


   form_child_frame::form_child_frame(sp(::base::application) papp):
      element(papp),
      simple_child_frame(papp),
      ::form_child_frame(papp)
   {

   }


} // namespace filemanager