#pragma once

#include "user_keyboard_focus.h"
#include "user_mouse_focus.h"

namespace user
{

   class elemental;


   class CLASS_DECL_ca element_2d : 
      virtual public keyboard_focus,
      virtual public mouse_focus
   {
   public:
      point            m_pt;
      size            m_size;
      rect      m_rectView;

      virtual void _001OnCalcLayout(::ca::graphics * pdc);
      virtual void _001OnDraw(user::elemental * pview, ::ca::graphics * pdc);

      virtual bool hit_test(int x, int y);

      virtual void _001OnLButtonDown(user::elemental * pview, gen::signal_object * pobj);
      virtual void _001OnLButtonUp(user::elemental * pview, gen::signal_object * pobj);
      virtual void _001OnMouseMove(user::elemental * pview, gen::signal_object * pobj);

      virtual ::ca::application * get_app();

   };

} // namespace user