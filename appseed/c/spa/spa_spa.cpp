#include "StdAfx.h"

bool g_bAdmin = false;
vsstring * g_pstrId = NULL;


CLASS_DECL_____ bool spa_get_admin()
{
   return g_bAdmin;
}

CLASS_DECL_____ void spa_set_admin(bool bSet)
{
   g_bAdmin = bSet;
}

CLASS_DECL_____ vsstring spa_get_id()
{
   return *g_pstrId;
}

CLASS_DECL_____ void spa_set_id(const char * psz)
{
   if(g_pstrId == NULL)
   {
      g_pstrId = new vsstring;
   }
   *g_pstrId = psz;
}


CLASS_DECL_____ vsstring spa_get_platform()
{
#ifdef _X86_
   return "x86";
#else
   return "x64";
#endif
}


bool is_installed(const char * psz)
{

   if(psz == NULL)
      return true;

   if(*psz == '\0')
      return true;


   XNode nodeInstall;

   nodeInstall.Load(file_get_contents_dup(dir::appdata("spa_install.xml")));

   LPXNode lpnodeInstalled = nodeInstall.GetChild("installed");

   if(lpnodeInstalled != NULL)
   {
      for(int ui = 0; ui < lpnodeInstalled->childs.get_count(); ui++)
      {
         vsstring strId = lpnodeInstalled->childs[ui]->GetAttrValue("id");
         if(strId == psz)
         {
            return true;
         }
      }
   }
   return false;
}
