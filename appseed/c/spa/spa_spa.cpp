#include "framework.h"


bool g_bAdmin = false;

vsstring * g_pstrId = NULL;


CLASS_DECL_c bool spa_get_admin()
{
   return g_bAdmin;
}

CLASS_DECL_c void spa_set_admin(bool bSet)
{
   g_bAdmin = bSet;
}

CLASS_DECL_c vsstring spa_get_id()
{
   return *g_pstrId;
}

CLASS_DECL_c void spa_set_id(const char * psz)
{
   if(g_pstrId == NULL)
   {
      g_pstrId = new vsstring;
   }
   *g_pstrId = psz;
}


CLASS_DECL_c vsstring spa_get_platform()
{
#ifdef X86
   return "x86";
#else
   return "x64";
#endif
}


bool is_installed(const char * pszVersion, const char * pszBuild, const char * pszType, const char * psz, const char * pszLocale, const char * pszSchema)
{

   if(psz == NULL)
      return true;

   if(*psz == '\0')
      return true;

   if(pszType == NULL || *pszType == '\0')
      pszType = "application";

   if(pszVersion == NULL || *pszVersion == '\0')
      return false;

   if(stricmp_dup(pszVersion, "basis") && stricmp_dup(pszVersion, "stage"))
      return false;

   XNode nodeInstall;

   nodeInstall.Load(file_as_string_dup(dir::appdata("spa_install.xml")));

   LPXNode lpnodeVersion = nodeInstall.GetChild(pszVersion);

   if(lpnodeVersion == NULL)
      return false;

   LPXNode lpnodeInstalled = lpnodeVersion->GetChildByAttr("installed", "build", pszBuild);

   if(lpnodeInstalled == NULL)
      return false;

   LPXNode lpnodeType = lpnodeInstalled->GetChild(pszType);

   if(lpnodeType == NULL)
      return false;

   LPXNode lpnodeId = NULL;

   for(int32_t ui = 0; ui < lpnodeType->childs.get_count(); ui++)
   {

      lpnodeId = lpnodeType->childs[ui];

      vsstring strId = lpnodeId->GetAttrValue("id");

      if(!strcmp(lpnodeId->name, pszType) && strId == psz)
      {

         goto found_id;

      }

   }

   return false;

found_id:

   LPXNode lpnodeLocalization = NULL;

   for(int32_t ui = 0; ui < lpnodeId->childs.get_count(); ui++)
   {

      lpnodeLocalization = lpnodeId->childs[ui];

      vsstring strLocale = lpnodeLocalization->GetAttrValue("locale");
      vsstring strSchema = lpnodeLocalization->GetAttrValue("schema");

      if(!strcmp(lpnodeLocalization->name, "localization") && strLocale == pszLocale && strSchema == pszSchema)
      {

         return true;

      }

   }

   return false;

}

static simple_string_to_string g_strmapLatestBuildNumber;

uint32_t g_dwLatestBuildNumberLastFetch = 0;

CLASS_DECL_c vsstring get_latest_build_number(const char * pszVersion)
{

   vsstring strLatestBuildNumber = g_strmapLatestBuildNumber[pszVersion];

   if(!strLatestBuildNumber.is_empty() && (get_tick_count() - g_dwLatestBuildNumberLastFetch) < ((1984 + 1977) * 3))
      return strLatestBuildNumber;

   return fetch_latest_build_number(pszVersion);

}

CLASS_DECL_c vsstring fetch_latest_build_number(const char * pszVersion)
{

   vsstring strBuildNumber;

   vsstring strSpaIgnitionBaseUrl;

   if(pszVersion != NULL && !strcmp(pszVersion, "basis"))
   {

       strSpaIgnitionBaseUrl = "http://basis.spaignition.api.server.ca2.cc";

   }
   else if(pszVersion != NULL && !strcmp(pszVersion, "stage"))
   {

       strSpaIgnitionBaseUrl = "http://stage.spaignition.api.server.ca2.cc";

   }
   else
   {

#if CA2_PLATFORM_VERSION == CA2_BASIS

      strSpaIgnitionBaseUrl = "http://basis.spaignition.api.server.ca2.cc";

#else

      strSpaIgnitionBaseUrl = "http://stage.spaignition.api.server.ca2.cc";

#endif

   }

   int32_t iRetry = 0;

RetryBuildNumber:

   if(iRetry > 10)
   {

      g_dwLatestBuildNumberLastFetch = get_tick_count();

      g_strmapLatestBuildNumber.set_at(pszVersion, "");

      return "";

   }

   iRetry++;

   strBuildNumber = ms_get_dup(strSpaIgnitionBaseUrl + "/query?node=build", false, NULL, NULL);

   strBuildNumber.trim();

   if(strBuildNumber.length() != 19)
   {

      Sleep(184 * iRetry);

      goto RetryBuildNumber;

   }

   g_dwLatestBuildNumberLastFetch = get_tick_count();

   g_strmapLatestBuildNumber.set_at(pszVersion, strBuildNumber);

   return strBuildNumber;

}
