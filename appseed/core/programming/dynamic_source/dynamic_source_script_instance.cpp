#include "framework.h"


namespace dynamic_source
{


   script_instance::script_instance(script * pscript) :
      element(pscript->get_app())
   {
      m_pscript = pscript;
      m_pscriptScriptInstance = pscript;
      m_pscriptScriptInstance->m_scriptinstanceptra.add(this);
   }

   script_instance::~script_instance()
   {
   }

   void script_instance::destroy()
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
      //m_pscriptScriptInstance.release();
//      m_pscript.release();
   }


   void script_instance::set_session_value(id, var)
   {
   
   }


   var script_instance::get_session_value(id)
   {
      
      return var(var::type_new);

   }
   
   string script_instance::session_id(const char *)
   {

      return "";

   }


} // namespace dynamic_source



