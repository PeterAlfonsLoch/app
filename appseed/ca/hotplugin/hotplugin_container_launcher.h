#pragma once


namespace hotplugin
{


   class CLASS_DECL_ca container_launcher :
      virtual public ::launcher
   {
   public:

      vsstring m_strChannel;

      container_launcher(const char * pszChannel);
         
      virtual bool ensure_executable() { return true; }

      vsstring get_params();

      virtual vsstring get_executable_path();

   };


} // namespace ca2plugin_container



