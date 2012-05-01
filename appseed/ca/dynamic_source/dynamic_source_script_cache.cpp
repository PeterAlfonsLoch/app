#include "StdAfx.h"


namespace dynamic_source
{


   script_cache::script_cache(::ca::application * papp) :
      ca(papp)
   {

   }

   script_cache::~script_cache(void)
   {
      POSITION pos = m_map.get_start_position();
      string strKey;
      script * pscript = NULL;
      while(pos != NULL)
      {
         m_map.get_next_assoc(pos, strKey, (void * &) pscript);
         try
         {
            if(pscript != NULL)
            {
               delete pscript;
            }
         }
         catch(...)
         {
         }
      }
   }


   script * script_cache::get(const char * lpcszName)
   {

      single_lock sl(&m_cs, TRUE);

      map_string_to_ptr::pair * ppair = m_map.PLookup(lpcszName);

      if(ppair != NULL)
         return (script *) ppair->m_value;

      script * pscript = new ds_script(get_app());

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = lpcszName;

      cache(pscript);

      return pscript;

   }

   script * script_cache::register_script(const char * lpcszName, script * pscript)
   {

      single_lock sl(&m_cs, TRUE);

      map_string_to_ptr::pair * ppair = m_map.PLookup(lpcszName);

      if(ppair != NULL)
      {
         try
         {
            delete (script *) ppair->m_value;
         }
         catch(...)
         {
         }

         ppair->m_value = pscript;

         return pscript;

      }

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = lpcszName;

      cache(pscript);

      return pscript;

   }

   script_instance * script_cache::create_instance(const char * lpcszName)
   {

      if(gen::str::begins(lpcszName, "netnode://"))
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
      script * pscript = NULL;
      string strName;
      POSITION pos = m_map.get_start_position();
      while(pos != NULL)
      {
         m_map.get_next_assoc(pos, strName, (void * &) pscript);

         ds_script * pdsscript = dynamic_cast < ds_script * > (pscript);
         if(pdsscript != NULL)
         {
            pdsscript->m_bShouldBuild = true;
         }

      }
   }


} // namespace dynamic_source


