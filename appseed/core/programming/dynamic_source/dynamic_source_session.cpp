#include "framework.h"


namespace dynamic_source
{


   session::session(const string & strId, ::dynamic_source::script_manager * pmanager) :
      element(pmanager->get_app()),
      m_pmanager(pmanager),
      m_mutex(pmanager->get_app()),
      m_strId(strId)
   {
   }

   session::~session()
   {
      ::str::international::locale_schema * pls = m_set["locale_schema"].cast < ::str::international::locale_schema > ();
      if(pls != NULL)
      {
         ::output_debug_string("locale_schema.m_idLocale=" + pls->m_idLocale.str());
      }
      if(m_set.has_property("rsa_n"))
      {
         ::output_debug_string("rsa_n");
      }
   }

   int64_t session::add_ref()
   {

      if(get_ref_count() == 0)
      {
         
         root::add_ref();

         single_lock sl(&m_pmanager->m_mutexSession, true);
         
         m_pmanager->m_mapSession.set_at(m_strId, this);

         m_pmanager->m_mapSessionExpiry.remove_key(m_strId);

         return m_countReference;

      }
      else
      {
      
         return root::add_ref();

      }

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

      return root::dec_ref();

   }


} // namespace dynamic_source





