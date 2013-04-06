#include "framework.h"


namespace dynamic_source
{


   script_cache::script_cache(sp(::ca::application) papp) :
      ca(papp)
   {

   }

   script_cache::~script_cache()
   {

   }


   script * script_cache::get(const char * lpcszName)
   {

      string strName(lpcszName);

#ifdef WINDOWS
      strName.replace("/", "\\");
#endif

      single_lock sl(&m_cs, TRUE);

      strsp(script)::pair * ppair = m_map.PLookup(strName);

      if(ppair != ::null())
         return (script *) ppair->m_element2;

      sp(script) pscript = new ds_script(get_app());

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = strName;

      cache(pscript);

      return pscript;

   }

   script * script_cache::register_script(const char * lpcszName, script * pscript)
   {

      string strName(lpcszName);

#ifdef WINDOWS
      strName.replace("/", "\\");
#endif

      single_lock sl(&m_cs, TRUE);

      strsp(script)::pair * ppair = m_map.PLookup(strName);

      if(ppair != ::null())
      {

         ppair->m_element2 = pscript;

         return pscript;

      }

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = strName;

      cache(pscript);

      return pscript;

   }

   script_instance * script_cache::create_instance(const char * lpcszName)
   {

      if(::ca::str::begins(lpcszName, "netnode://"))
      {
         single_lock sl(&m_cs, TRUE);
         script * pscript  = get(lpcszName);
         sl.unlock();
         return pscript->create_instance();
      }

      //::OutputDebugString(lpcszName);
      string strName(lpcszName);
      strName = m_pmanager->real_path(lpcszName);
      //::OutputDebugString(strName);
      if(strName.is_empty())
         strName =  m_pmanager->real_path(string(lpcszName) + ".ds");
      //::OutputDebugString(strName);
      strName.replace("\\", "/");
      single_lock sl(&m_cs, TRUE);
      script * pscript  = get(strName);
      sl.unlock();
      return pscript->create_instance();
   }


   void script_cache::cache(script * pscript)
   {
      single_lock sl(&m_cs, TRUE);
      m_map.set_at(pscript->m_strName, pscript);
   }

   void script_cache::set_all_out_of_date()
   {
      single_lock sl(&m_cs, TRUE);
      sp(script) pscript;
      string strName;
      POSITION pos = m_map.get_start_position();
      while(pos != ::null())
      {
         m_map.get_next_assoc(pos, strName, pscript);

         ds_script * pdsscript = dynamic_cast < ds_script * > (pscript.m_p);
         if(pdsscript != ::null())
         {
            pdsscript->m_bShouldBuild = true;
         }

      }
   }


} // namespace dynamic_source


