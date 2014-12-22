#pragma once


namespace hotplugin
{


   class CLASS_DECL_AXIS container_launcher :
      virtual public ::launcher
   {
   public:

      string m_strChannel;

      container_launcher(const char * pszChannel);
         
      virtual bool ensure_executable() { return true; }

      string get_params();

      virtual string get_executable_path();

   };


} // namespace ca2plugin_container



