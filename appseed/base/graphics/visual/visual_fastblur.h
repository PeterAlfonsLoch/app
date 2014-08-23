// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
#pragma once


namespace visual
{

   class CLASS_DECL_CORE fastblur :
      public ::visual::dib_sp
   {
   public:


      size           m_size;
      int32_t        m_iRadius;
      byte_array     m_uchaR;
      byte_array     m_uchaG;
      byte_array     m_uchaB;
      byte_array     m_uchaA;
      byte_array     m_ucha;
      byte_array     m_uchaDiv;
      int64_array    m_iaVmin;
      int64_array    m_iaVmax;



      fastblur(allocatorsp allocer);


      bool initialize(int32_t cx, int32_t cy, int32_t iRadius);
      bool initialize(size sz, int32_t iRadius);


      virtual bool blur();

      static bool s_fastblur(uint32_t * pdata, int32_t w, int32_t h, int32_t radius, byte * r, byte * g, byte * b, byte * a, byte * dv, int32_t stride, int32_t * vmin, int32_t * vmax);
      static bool s_fastblur(uint32_t * pdata, int32_t w, int32_t h, int32_t radius, uint32_t * prgba, byte * dv, int32_t stride);

   };

} // namespace visual
