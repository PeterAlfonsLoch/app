#pragma once


namespace aura
{


   class CLASS_DECL_AURA session_interface:
      virtual public ::aura::application_interface
   {
   public:


      session_interface *     m_pplatformcomposite;


      session_interface();
      virtual ~session_interface();


      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor,LPRECT lprect);


      //virtual ::visual::cursor * get_cursor();
      //virtual ::visual::cursor * get_default_cursor();



   };


} // namespace aura
















