#include "StdAfx.h"

bool is_file_ok(const char * path1, const char * pszTemplate)
{
   char get[1024];
   strcpy_dup(get, "http://spaignition.api.veriterse.net/md5?authnone&stage=");
   strcat_dup(get, pszTemplate);
   return file_exists_dup(path1) && !stricmp_dup(get_file_md5(path1), ms_get_dup(get));
}

