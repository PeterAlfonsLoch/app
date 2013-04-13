#include "framework.h"

namespace user
{

   tab_control::tab_control(sp(::ca::application) papp) :
      ca(papp),
      ::user::tab(papp),
      place_holder_container(papp)
   {
      get_data()->m_bCreated     = false;
      get_data()->m_iTabHeight   = 16;
   }

   tab_control::~tab_control()
   {
   }

} // namespace user