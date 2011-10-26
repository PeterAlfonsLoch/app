#pragma once

namespace plugin
{

   class CLASS_DECL_ca history :
      virtual public ca::history
   {
   public:

      
      plugin * m_pplugin;


      history(::ca::application * papp, plugin * pplugin);
         
   
      virtual bool hist(const char *pszUrl);

   };


} // namespace plugin