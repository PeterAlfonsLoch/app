#pragma once


namespace user
{

   extern CLASS_DECL_BASE critical_section * g_pcsUi;

   extern CLASS_DECL_BASE map < oswindow,oswindow,::user::interaction *,::user::interaction * > * g_pmapUi;

   CLASS_DECL_BASE void init_windowing();

   CLASS_DECL_BASE void term_windowing();


} // namespace user





CLASS_DECL_BASE bool oswindow_assign(oswindow oswindow, ::user::interaction * pui);
CLASS_DECL_BASE int_bool oswindow_remove(::user::interaction * pui);
CLASS_DECL_BASE ::user::interaction * oswindow_get(oswindow oswindow);


//#if defined(WINDOWS) || defined(LINUX)
//
//inline ::user::interaction * window_from_handle(oswindow oswindow);
//
//inline ::user::interaction * window_from_handle(oswindow oswindow)
//{
//
//   if(oswindow == NULL)
//   {
//
//      return NULL;
//
//   }
//
//   cslock slOsWindow(::user::g_pcsUi);
//
//   return ::user::g_pmapUi->operator[](oswindow);
//
//}
//
//#else
//
//CLASS_DECL_BASE ::user::interaction * window_from_handle(oswindow oswindow);
//
//#endif
