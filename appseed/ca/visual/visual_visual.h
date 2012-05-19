#pragma once

namespace visual
{

   class CLASS_DECL_ca visual
   {
   public:
      visual(::ca::graphics * pdc);

      virtual void Polygon(const point_array & pointa);

      ::ca::graphics * m_pdc;

   public:
      virtual ~visual();
   };

} // namespace visual