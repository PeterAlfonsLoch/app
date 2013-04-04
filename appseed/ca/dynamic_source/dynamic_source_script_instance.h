#pragma once


namespace dynamic_source
{

   
   class script;

   
   class CLASS_DECL_ca script_instance :
      virtual public script_interface
   {
   public:


      uint32_t             m_dwCreate;
      sp(script)           m_pscriptScriptInstance;

      string               m_strDebugRequestUri;
      string               m_strDebugThisScript;


      script_instance(script * pscript);
      virtual ~script_instance();

      void destroy();

   };


} // namespace dynamic_source


