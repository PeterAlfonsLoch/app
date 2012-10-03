#pragma once


namespace plugin
{


   class plugin;


   class CLASS_DECL_ca system :
      virtual public ::plane::system
   {
   public:


      plugin * m_pplugin;


      system(::ca::application * papp);


      virtual bool open_link(const char * pszLink, const char * pszTarget);
      
      virtual bool os_native_bergedge_start();

      virtual bool verb();

      virtual string get_host_location_url();

   };


} // namespace plugin



