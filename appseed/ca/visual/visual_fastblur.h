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
      virtual public ::visual::dib_sp
   {
   public:


      size           m_size;
      int            m_iRadius;
      byte_array     m_ucha;
      byte_array     m_uchaDiv;


      fastblur(::ca::application * papp);


      bool initialize(int cx, int cy, int iRadius);
      bool initialize(size sz, int iRadius);


      virtual bool blur();

   };

} // namespace visual
