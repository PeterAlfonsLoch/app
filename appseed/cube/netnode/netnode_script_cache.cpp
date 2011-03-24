#include "StdAfx.h"
#include "netnodeScriptCache.h"
#include "netnodeScriptCompiler.h"

netnodeScriptCache::netnodeScriptCache(::ca::application * papp) :
   ca(papp)
{

}

netnodeScriptCache::~netnodeScriptCache(void)
{
}


netnodeScript * netnodeScriptCache::get(const char * lpcszName)
{
   CSingleLock sl(&m_cs, TRUE);

   string strName(lpcszName);
   if(System.file().extension(strName).is_empty())
   {
      strName += ".ds";
   }

   netnodeScript * pscript;
   if(m_map.Lookup(strName, (void *&) pscript))
   {
      return pscript;
   }
     pscript = new netnodeScript(get_app());
   pscript->m_pmanager = m_pmanager;
   pscript->m_strName = strName;
   cache(pscript);
   return pscript;
}

netnodeScriptInstance * netnodeScriptCache::create_instance(const char * lpcszName)
{
   string strName(lpcszName);
   strName = m_pmanager->real_path(lpcszName);
   if(strName.is_empty())
      strName =  m_pmanager->real_path(string(lpcszName) + ".ds");
   strName.replace("\\", "/");
   CSingleLock sl(&m_cs, TRUE);
   netnodeScript * pscript  = get(strName);
   sl.Unlock();
   CSingleLock slScript(&pscript->m_mutex, TRUE);
   if(pscript->ShouldBuild())
   {
      string str;
      int iRetry = 0;
      do
      {
         m_pmanager->m_pcompiler->compile(pscript);
         pscript->Load(false);
         pscript->m_memfileError.seek_to_begin();
         pscript->m_memfileError.to_string(str);
         if(iRetry == 0)
         {
            TRACE("Build: %s\n%s\n", pscript->m_strName, str);
         }
         else
         {
            TRACE("Retry(%d): %s\nError: %s\n", iRetry, pscript->m_strName, str);
         }
         iRetry++;
      } while(pscript->HasTempError() && iRetry < 84);
   }
   return pscript->create_instance();
}


void netnodeScriptCache::cache(netnodeScript * pscript)
{
   CSingleLock sl(&m_cs, TRUE);
   m_map.set_at(pscript->m_strName, pscript);
}

void netnodeScriptCache::set_all_out_of_date()
{
   CSingleLock sl(&m_cs, TRUE);
   netnodeScript * pscript = NULL;
   string strName;
   POSITION pos = m_map.get_start_position();
   while(pos != NULL)
   {
      m_map.get_next_assoc(pos, strName, (void * &) pscript);
      pscript->m_bShouldBuild = true;
   }
}
