#include "framework.h"


bool g_bAdmin = false;

string * g_pstrId = NULL;


CLASS_DECL_ca bool spa_get_admin()
{
   return g_bAdmin;
}

CLASS_DECL_ca void spa_set_admin(bool bSet)
{
   g_bAdmin = bSet;
}

CLASS_DECL_ca string spa_get_id()
{
   return *g_pstrId;
}

CLASS_DECL_ca void spa_set_id(const char * psz)
{
   if(g_pstrId == NULL)
   {
      g_pstrId = new string;
   }
   *g_pstrId = psz;
}


CLASS_DECL_ca string spa_get_platform()
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
   {

#if CA2_PLATFORM_VERSION == CA2_BASIS

      pszVersion = "basis";

#else

      pszVersion = "stage";

#endif

   }

   string strLatestBuildNumber;

   if(pszBuild == NULL || *pszBuild == '\0')
   {

      strLatestBuildNumber = get_latest_build_number(pszVersion);

      pszBuild = strLatestBuildNumber;

   }

   if(stricmp_dup(pszVersion, "basis") && stricmp_dup(pszVersion, "stage"))
      return false;

   ::xml::document nodeInstall;

   nodeInstall.load(file_as_string_dup(dir::appdata("spa_install.xml")));

   ::xml::node * lpnodeVersion = nodeInstall.get_child(pszVersion);

   if(lpnodeVersion == NULL)
      return false;

   ::xml::node * lpnodeInstalled = lpnodeVersion->GetChildByAttr("installed", "build", pszBuild);

   if(lpnodeInstalled == NULL)
      return false;

   ::xml::node * lpnodeType = lpnodeInstalled->get_child(pszType);

   if(lpnodeType == NULL)
      return false;

   ::xml::node * lpnodeId = NULL;

   for(int32_t ui = 0; ui < lpnodeType->get_children_count(); ui++)
   {

      lpnodeId = lpnodeType->child_at(ui);

      string strId = lpnodeId->attr("id");

      if(!strcmp(lpnodeId->get_name(), pszType) && strId == psz)
      {

         goto found_id;

      }

   }

   return false;

found_id:

   ::xml::node * lpnodeLocalization = NULL;

   for(int32_t ui = 0; ui < lpnodeId->get_children_count(); ui++)
   {

      lpnodeLocalization = lpnodeId->child_at(ui);

      string strLocale = lpnodeLocalization->attr("locale");
      string strSchema = lpnodeLocalization->attr("schema");

      if(!strcmp(lpnodeLocalization->get_name(), "localization") && strLocale == pszLocale && strSchema == pszSchema)
      {

         return true;

      }

   }

   return false;

}

static string_to_string g_strmapLatestBuildNumber;

uint32_t g_dwLatestBuildNumberLastFetch = 0;

CLASS_DECL_ca string get_latest_build_number(const char * pszVersion)
{

   string strLatestBuildNumber = g_strmapLatestBuildNumber[pszVersion];

   if(!strLatestBuildNumber.is_empty() && (get_tick_count() - g_dwLatestBuildNumberLastFetch) < ((1984 + 1977) * 3))
      return strLatestBuildNumber;

   return fetch_latest_build_number(pszVersion);

}

CLASS_DECL_ca string fetch_latest_build_number(const char * pszVersion)
{

   string strBuildNumber;

   string strSpaIgnitionBaseUrl;

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

   strBuildNumber = http_get_dup(strSpaIgnitionBaseUrl + "/query?node=build", false, NULL, NULL);

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
