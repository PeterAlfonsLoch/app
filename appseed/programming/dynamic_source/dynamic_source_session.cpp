#include "framework.h"
#include "dynamic_source.h"


namespace dynamic_source
{


session::session(const string & strId, ::dynamic_source::script_manager * pmanager) :
   ::object(pmanager->get_app()),
    m_pmanager(pmanager),
    m_mutex(pmanager->get_app()),
    m_strId(strId)
{
}

session::~session_parent
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

   return object::add_ref();

}

int64_t session::release()
{

   return object::dec_ref();

}


} // namespace dynamic_source





