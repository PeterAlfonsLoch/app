#include "framework.h"
#include "math_number.h"

namespace math
{


   number::number()
   {
      m_pimpl = new value_impl;
   }

   number::~number()
   {
      delete m_pimpl;
   }


} // namespace math