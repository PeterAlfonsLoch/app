#pragma once


namespace plugin
{


   class plugin;


   class CLASS_DECL_CORE system :
      virtual public ::core::system
   {
   public:


      plugin * m_pplugin;


      system(sp(::aura::application) papp);


      virtual bool open_link(const string & pszLink, const string & pszTarget);
      
      virtual bool os_native_bergedge_start();

      virtual bool verb();

      virtual string get_host_location_url();

   };


} // namespace plugin



