#pragma once


namespace plugin
{


   class run_start_installer :
      virtual public ::plane::bergedge::run_start_installer
   {
   public:

      
      plugin * m_pplugin;


      run_start_installer(::ca::application * papp, plugin * pplugin);
         
   
      virtual void run_start_install(const char * pszStart);

   };


} // namespace plugin