#pragma once


namespace user
{

   extern CLASS_DECL_AXIS critical_section * g_pcsUi;

   extern CLASS_DECL_AXIS map < oswindow,oswindow,::user::interaction *,::user::interaction * > * g_pmapUi;

   CLASS_DECL_AXIS void init_windowing();

   CLASS_DECL_AXIS void term_windowing();


} // namespace user





CLASS_DECL_AXIS bool oswindow_assign(oswindow oswindow, ::user::interaction * pui);
CLASS_DECL_AXIS int_bool oswindow_remove(::user::interaction * pui);



#if defined(WINDOWS) || defined(LINUX)

inline ::user::interaction * window_from_handle(oswindow oswindow);

inline ::user::interaction * window_from_handle(oswindow oswindow)
{

   if(oswindow == NULL)
   {

      return NULL;

   }

   cslock slOsWindow(::user::g_pcsUi);

   return ::user::g_pmapUi->operator[](oswindow);

}

#else

CLASS_DECL_AXIS ::user::interaction * window_from_handle(oswindow oswindow);

#endif
