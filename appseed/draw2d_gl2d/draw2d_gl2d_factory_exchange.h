#pragma once

namespace draw2d_gl2d
{

   class CLASS_DECL_DRAW2D_GL2D factory_exchange :
      virtual public ::object
   {
   public:
      factory_exchange(::aura::application * papp);
      virtual ~factory_exchange();
   };

} // namespace draw2d_gl2d