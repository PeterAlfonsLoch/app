#pragma once


namespace user
{

   CLASS_DECL_BASE void init_windowing();

   CLASS_DECL_BASE void term_windowing();


} // namespace user





CLASS_DECL_BASE ::user::interaction * window_from_handle(oswindow oswindow);
CLASS_DECL_BASE bool oswindow_assign(oswindow oswindow, ::user::interaction * pui);
CLASS_DECL_BASE bool oswindow_remove(::user::interaction * pui);
