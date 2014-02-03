#pragma once


namespace dynamic_source
{

   
   class script;

   
   class CLASS_DECL_CORE script_instance :
      virtual public script_interface
   {
   public:


      uint32_t             m_dwCreate;
      sp(script)           m_pscriptScriptInstance;



      script_instance(script * pscript);
      virtual ~script_instance();

      void destroy();


      virtual void set_session_value(id id, var value);
      virtual var get_session_value(id id);
      virtual string session_id(const char * pszId = NULL);


   };


} // namespace dynamic_source


