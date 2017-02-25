#include "framework.h"


namespace aura
{


   void trace_add_file_and_line::log_trace_str(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * psz) const
   {

      System.log().trace_str(pszFileName, nLine, dwCategory, nLevel, psz);

   }


} // namespace aura