#pragma once

namespace plugin
{

   class CLASS_DECL_BASE history :
      virtual public ::core::history
   {
   public:

      
      plugin * m_pplugin;


      history(sp(base_application) papp, plugin * pplugin);
         
   
      virtual bool hist(const char *pszUrl);

   };


} // namespace plugin