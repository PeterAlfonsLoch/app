#include "framework.h"


namespace dynamic_source
{


   session::session(const string & strId, ::dynamic_source::script_manager * pmanager) :
      ca(pmanager->get_app()),
      m_pmanager(pmanager),
      m_mutex(pmanager->get_app()),
      m_strId(strId)
   {
   }

   session::~session()
   {
      ::ca::international::locale_schema * pls = m_set["locale_schema"].ca < ::ca::international::locale_schema > ();
      if(pls != ::null())
      {
         ::OutputDebugString("locale_schema.m_idLocale=" + pls->m_idLocale.str());
      }
      if(m_set.has_property("rsa_n"))
      {
         ::OutputDebugString("rsa_n");
      }
   }

   int64_t session::add_ref()
   {

      if(get_ref_count() == 1)
      {

         single_lock sl(&m_pmanager->m_mutexSession, true);
         
         m_pmanager->m_mapSessionExpiry.remove_key(m_strId);

         m_pmanager->m_mapSession.set_at(m_strId, this);

      }

      return ::c::c::add_ref();

   }

   int64_t session::release()
   {

      if(get_ref_count() == 2)
      {

         single_lock sl(&m_pmanager->m_mutexSession, true);
         
         m_timeExpiry = ::datetime::time::get_current_time();

         m_timeExpiry += minutes(2);

         m_pmanager->m_mapSessionExpiry.set_at(m_strId, this);

         m_pmanager->m_mapSession.remove_key(m_strId);

      }

      return ::c::c::release();

   }


} // namespace dynamic_source





