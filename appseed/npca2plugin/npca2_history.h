#pragma once

namespace npca2
{

   class history :
      virtual public ca::history
   {
   public:

      
      plugin * m_pplugin;


      history(::ca::application * papp, plugin * pplugin);
         
   
      virtual bool hist(const char *pszUrl);

   };


} // namespace npca2