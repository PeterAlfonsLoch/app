#pragma once


namespace plugin
{


   class CLASS_DECL_ca2 instance : 
      public ::plugin::plugin
   {
   public:

   
   
      oswindow                          m_oswindow;
      bool                          m_bStream;
   


      instance();
      virtual ~instance();


      uint16_t HandleEvent(void * pvoid);


      virtual host_interaction * create_host_interaction();

      void shut();

      virtual bool initialize();


   };


} // namespace plugin