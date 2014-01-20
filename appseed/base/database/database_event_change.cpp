#include "framework.h"


namespace database
{

   change_event::change_event() :
      m_pvar(NULL)
   {
      m_pserver = NULL;
      m_puh = NULL;
      m_bOk = true;
   }

   change_event::change_event(var & var) :
      m_pvar(&var)
   {
      m_pserver = NULL;
      m_puh = NULL;
      m_bOk = true;
   }

   bool change_event::data_get(::file::serializable & obj)
   {
      if(m_pserver != NULL)
      {
         return m_pserver->data_server_load(
            m_key.m_pclient,
            m_key.m_idSection,
            m_key.m_idKey,
            m_key.m_idIndex,
            obj);
      }
      return false;
   }


} // namespace database

