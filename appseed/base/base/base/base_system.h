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

         sp(::user::interaction)                      m_pui;
         ::axis::system_window ^                      m_pwindow;


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


      system(::aura::application * papp);
      virtual ~system();

      virtual bool defer_create_system_frame_window();

      virtual int32_t exit_application() override;

      virtual ::aura::session * on_create_session() override;

      virtual index get_ui_wkspace(::user::interaction * pui);

      virtual void set_active_guie(::user::interaction * pui);
      virtual void set_focus_guie(::user::interaction * pui);



      bool get_monitor_rect(index iMonitor,LPRECT lprect) override;
      ::count get_monitor_count() override;

      bool get_wkspace_rect(index iWkspace,LPRECT lprect) override;

      virtual ::user::interaction * ui_from_handle(void * pdata) override;

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




