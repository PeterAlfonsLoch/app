#pragma once


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system,
      virtual public :: base ::application
   {
   public:

#ifdef WINDOWSEX


      ::base::system_interaction_impl *            m_psystemwindow;

#endif

      ::user::schema *                             m_pschemaLayeredFrame;


      ::user::window_draw *                        m_ptwf;



      system(::aura::application * papp);
      virtual ~system();

      virtual bool defer_create_system_frame_window();

      virtual int32_t exit_instance();

      virtual ::aura::session * on_create_session();

      ::user::window_draw *                         get_twf();
      virtual index get_ui_wkspace(::user::interaction * pui);
      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();


      virtual bool initialize_twf();





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




