#include "StdAfx.h"


namespace dynamic_source
{


   script_instance::script_instance(script * pscript) :
      ca(pscript->get_app())
   {
      m_pscript = pscript;
      m_pscriptScriptInstance = pscript;
   }

   script_instance::~script_instance()
   {
      single_lock sl(&m_pscriptScriptInstance->m_mutex);
      try
      {
         sl.lock(minutes(1.0));
      }
      catch(...)
      {
      }
      try
      {
         m_pscriptScriptInstance->m_scriptinstanceptra.remove(this);
      }
      catch(...)
      {
      }
   }

   void script_instance::destroy()
   {
      delete this;
   }



} // namespace dynamic_source



