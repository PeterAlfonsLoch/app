#pragma once


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system,
      virtual public :: base ::application
   {
   public:

#if defined METROWIN && defined(__cplusplus_winrt)

      class os_system_window
      {
      public:

         bool                                         m_bWindowSizeChange;
         sp(::user::interaction)                      m_pui;
         ::axis::system_window ^                      m_pwindow;

         os_system_window();

   };

#elif defined(APPLE_IOS)
      
      class os_system_window
      {
      public:

         sp(::user::interaction)                      m_pui;


      };

#elif defined(VSNORD)

      class os_system_window
      {
      public:

         sp(::user::interaction)                      m_pui;
         oswindow                                     m_oswindow;


      };

#else

      class os_system_window;

#endif

#ifdef WINDOWSEX


      ::base::system_interaction_impl *            m_psystemwindow;

#endif

      sp(::user::schema)                           m_pschemaLayeredFrame;


      os_system_window *                           m_possystemwindow;
      ::visual::visual                             m_visual;








      system(::aura::application * papp);
      virtual ~system();

      virtual bool defer_create_system_frame_window();

      virtual bool process_initialize() override;
      virtual int32_t exit_application() override;

      virtual ::aura::session * on_create_session() override;

      virtual index get_ui_wkspace(::user::interaction * pui);

      virtual void set_active_guie(::user::interaction * pui);
      virtual void set_focus_guie(::user::interaction * pui);

      inline class ::visual::visual                & visual() { return m_visual; }


      //virtual ::install::canvas * install_create_canvas() override;
      //virtual void install_canvas_on_paint(::draw2d::graphics * pgraphics, const RECT & rect);
      //virtual int install_canvas_increment_mode() override;



      virtual DWORD get_monitor_color_temperature(index iMonitor);
      virtual bool adjust_monitor(index iMonitor, DWORD dwTemperature, double dBrightness, double dwGamma);
      virtual bool get_monitor_rect(index iMonitor,LPRECT lprect) override;
      virtual ::count get_monitor_count() override;

      bool get_wkspace_rect(index iWkspace,LPRECT lprect) override;

      virtual ::user::interaction_impl * impl_from_handle(void * pdata) override;
      virtual ::user::interaction * ui_from_handle(void * pdata) override;
      
      virtual void on_setting_changed(::aura::e_setting) override;
      
   };


} // namespace base



template < size_t _Bits >
inline ::file::ostream & operator << (::file::ostream & _Ostr,const bitset<_Bits>& _Right)
{
   // insert bitset as a string
   return (_Ostr << _Right.template to_string());
}

// TEMPLATE operator>>
template < size_t _Bits >
inline ::file::istream & operator >>(::file::istream &  _Istr,bitset<_Bits>& _Right)
{
   // extract bitset as a string
   string _Str;

   _Istr >> _Str;

   _Right = bitset<_Bits>(_Str);	// convert string and store

   return (_Istr);

}




void CLASS_DECL_BASE __start_system(::base::system * psystem);




