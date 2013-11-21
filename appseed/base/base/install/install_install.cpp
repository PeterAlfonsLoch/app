#include "framework.h"


namespace install
{

   install::install(sp(base_application) papp) :
      element(papp),
      ::base_departament(papp)
   {

   }

   install::~install()
   {

   }

   int_bool install::is_file_ok(const char * path1, const char * pszTemplate)
   {
      string strUrl;
#if CA2_PLATFORM_VERSION == CA2_BASIS
      strUrl = "http://basis.spaignition.api.server.ca2.cc/md5?authnone&version=basis&stage=";
#else
      strUrl = "http://stage.spaignition.api.server.ca2.cc/md5?authnone&version=stage&stage=";
#endif
      strUrl += pszTemplate;

      return file_exists_dup(path1) && !stricmp_dup(get_file_md5(path1), Application.http().get(strUrl));

   }


} // namespace spa