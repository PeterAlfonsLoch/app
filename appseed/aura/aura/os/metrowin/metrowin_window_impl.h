#pragma once



namespace user
{


   class interaction;
   class interaction;


} // namespace user


struct CLASS_DECL_AURA oswindow_data
{
public:

   
   ::user::interaction * m_pui;

   ::user::interaction * window();

};


class oswindow_dataptra;



///static oswindow_dataptra * s_pdataptra;
CLASS_DECL_AURA bool oswindow_find(::user::interaction * pui);
CLASS_DECL_AURA oswindow oswindow_get(::user::interaction * pui);
CLASS_DECL_AURA bool oswindow_remove(::user::interaction * pui);
#if defined(__cplusplus_winrt)
CLASS_DECL_AURA Windows::UI::Core::CoreWindow ^ get_os_window(oswindow window);
#endif
