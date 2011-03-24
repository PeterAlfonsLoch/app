#include "StdAfx.h"
#include "MediaLibraryViewUpdateHint.h"

namespace mplite
{

   MediaLibraryViewUpdateHint::MediaLibraryViewUpdateHint()
   {

   }

   MediaLibraryViewUpdateHint::~MediaLibraryViewUpdateHint()
   {

   }

   bool MediaLibraryViewUpdateHint::is_type_of(e_type e_type)
   {
      return m_etype == e_type;
   }

   void MediaLibraryViewUpdateHint::set_type(e_type e_type)
   {
      m_etype = e_type;
   }

} // namespace mplite