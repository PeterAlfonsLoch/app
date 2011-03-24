#include "StdAfx.h"
#include "OptionsViewUpdateHint.h"

namespace mplite
{

   OptionsViewUpdateHint::OptionsViewUpdateHint()
   {

   }

   OptionsViewUpdateHint::~OptionsViewUpdateHint()
   {

   }

   bool OptionsViewUpdateHint::is_type_of(e_type e_type)
   {
      return m_etype == e_type;
   }

   void OptionsViewUpdateHint::set_type(e_type e_type)
   {
      m_etype = e_type;
   }

} // namespace mplite