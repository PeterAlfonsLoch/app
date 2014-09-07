#include "framework.h" // from "axis/user/user.h"


namespace user
{


   view_update_hint::view_update_hint(sp(::aura::application) papp) :
      element(papp)
   {

      m_ehint     = hint_none;
      m_bOk       = true;

   }


   view_update_hint::~view_update_hint()
   {


   }


   bool view_update_hint::is_type_of(e_hint ehint) const
   {

      return m_ehint == ehint;

   }


} // namespace user









