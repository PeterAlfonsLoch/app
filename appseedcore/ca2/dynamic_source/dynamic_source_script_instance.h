#pragma once


namespace dynamic_source
{

   class CLASS_DECL_ca script_instance :
      public script_impl
   {
   public:


      DWORD       m_dwCreate;
      script *    m_pscriptScriptInstance;

      string m_strDebugRequestUri;
      string m_strDebugThisScript;


      script_instance(script * pscript);
      virtual ~script_instance();

      void destroy();


   };


} // namespace dynamic_source


