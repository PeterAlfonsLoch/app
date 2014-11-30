#pragma once


namespace dynamic_source
{

   
   class script;

   
   class CLASS_DECL_PROGRAMMING script_instance :
      virtual public script_interface
   {
   public:


      uint32_t             m_dwCreate;
      sp(script)           m_pscriptScriptInstance;



      script_instance(script * pscript);
      virtual ~script_instance();

      void destroy();




   };


} // namespace dynamic_source


