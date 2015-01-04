#pragma once


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system,
      virtual public :: base ::application
   {
   public:

#if defined METROWIN && defined(__cplusplus_winrt)

      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;
         ::base::system_window ^                      m_pwindow;


      };

#elif defined(APPLE_IOS)
      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;


      };

#elif defined(VSNORD)

      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;


      };

#else

      class os_data;

#endif

//      ::user::interaction *                        m_psimpleui;
      os_data *                                    m_posdata;



      string_map < int_to_string >                 m_mapEnumToName;
      string_map < string_to_int >                 m_mapNameToEnum;
      ::user::window_draw *                        m_ptwf;



      ::aura::library                              m_libraryDraw2d;


      bool                                         m_bSystemSynchronizedCursor;
      bool                                         m_bSystemSynchronizedScreen;


#ifdef WINDOWSEX


      ::base::system_interaction_impl *            m_psystemwindow;

      raw_array < MONITORINFO >                    m_monitorinfoa;
      raw_array < HMONITOR >                       m_hmonitora;
      raw_array < MONITORINFO >                    m_monitorinfoaDesk;

#endif

      ::user::schema *                             m_pschemaLayeredFrame;


      system(::aura::application * papp);
      virtual ~system();






      virtual void construct(const char * pszAppId);

      virtual bool initialize_instance();

      virtual int32_t exit_instance();
      virtual bool finalize();





      sp(::user::window_draw)                         get_twf();





      virtual bool verb();





      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

      virtual void wait_twf();

      virtual bool defer_create_system_frame_window();

      virtual bool is_system();




      virtual ::aura::document * place_hold(::user::interaction * pui);

      virtual sp(::aura::session) query_session(index iEdge);



      virtual bool initialize_twf();


      void enum_display_monitors();

#if defined(WINDOWS)
      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData);
      void monitor_enum(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor);
#endif

      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor,LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor,LPRECT lprect);

      virtual index get_ui_wkspace(::user::interaction * pui);
      virtual index get_main_wkspace(LPRECT lprect = NULL);
      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace,LPRECT lprect);
      virtual ::count get_desk_wkspace_count();
      virtual bool  get_desk_wkspace_rect(index iWkspace,LPRECT lprect);

      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();

/*
      virtual string get_ca2_module_folder();
      virtual string get_ca2_module_file_path();
      virtual string get_module_folder();
      virtual string get_module_file_path();
      virtual string get_module_title();
      virtual string get_module_name();
*/

      //virtual string dir_appmatter_locator(::aura::application * papp);

      virtual ::aura::session * on_create_session();



   };


} // namespace base



template < size_t _Bits >
inline ::file::output_stream & operator << (::file::output_stream & _Ostr,const bitset<_Bits>& _Right)
{
   // insert bitset as a string
   return (_Ostr << _Right.template to_string());
}

// TEMPLATE operator>>
template < size_t _Bits >
inline ::file::input_stream & operator >>(::file::input_stream &  _Istr,bitset<_Bits>& _Right)
{
   // extract bitset as a string
   string _Str;

   _Istr >> _Str;

   _Right = bitset<_Bits>(_Str);	// convert string and store

   return (_Istr);

}




void CLASS_DECL_BASE __start_system(::base::system * psystem);




