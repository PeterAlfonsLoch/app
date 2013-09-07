#include "framework.h"


int_bool is_file_ok(const char * path1, const char * pszTemplate)
{
   char get[1024];
#if CA2_PLATFORM_VERSION == CA2_BASIS
   strcpy_dup(get, "http://basis.spaignition.api.server.core.cc/md5?authnone&version=basis&stage=");
#else
   strcpy_dup(get, "http://stage.spaignition.api.server.core.cc/md5?authnone&version=stage&stage=");
#endif
   strcat_dup(get, pszTemplate);
   return file_exists_dup(path1) && !stricmp_dup(get_file_md5(path1), http_get_dup(get));
}

