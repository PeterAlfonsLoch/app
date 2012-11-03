#pragma once


namespace plugin
{


   class CLASS_DECL_ca instance : 
      public ::plugin::plugin
   {
   public:

   
   
      oswindow_                          m_hwnd;
      bool                          m_bStream;
   


      instance();
      virtual ~instance();


      uint16 HandleEvent(void * pvoid);


      virtual host_interaction * create_host_interaction();

      void shut();

      virtual bool initialize();


   };


} // namespace plugin