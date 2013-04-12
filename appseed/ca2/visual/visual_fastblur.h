// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//

#pragma once

namespace visual
{

   class CLASS_DECL_ca fastblur :
      public ::visual::dib_sp
   {
   public:


      size           m_size;
      int32_t            m_iRadius;
      byte_array     m_ucha;
      byte_array     m_uchaDiv;


      fastblur(::ca::allocatorsp allocer);


      bool initialize(int32_t cx, int32_t cy, int32_t iRadius);
      bool initialize(size sz, int32_t iRadius);


      virtual bool blur();

   };

} // namespace visual
