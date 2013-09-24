#pragma once



namespace user
{


   class interaction;
   class base_interaction;


} // namespace user


struct CLASS_DECL_c oswindow_data
{
public:

   
   ::user::base_interaction * m_pui;


   ::user::interaction * window();

};


class oswindow_dataptra;



///static oswindow_dataptra * s_pdataptra;
CLASS_DECL_c int_bool oswindow_find(::user::base_interaction * pui);
CLASS_DECL_c oswindow oswindow_get(::user::base_interaction * pui);
CLASS_DECL_c int_bool oswindow_remove(::user::base_interaction * pui);
#if defined(__cplusplus_winrt)
CLASS_DECL_c Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window(oswindow window);
#endif
