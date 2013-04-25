#include "framework.h"


namespace dynamic_source
{


   session::session(::ca::application * papp) :
      m_mutex(papp)
   {
   }

   session::~session()
   {
   }

   int64_t session::release()
   {

      if(get_ref_count() >= 2)
      {
         m_timeAccess = ::datetime::time::get_current_time();
      }

      int64_t i = ::c::c::release();

      return i;

   }


} // namespace dynamic_source





