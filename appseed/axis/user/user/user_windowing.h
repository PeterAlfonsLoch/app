#pragma once


namespace user
{

   CLASS_DECL_AXIS void init_windowing();

   CLASS_DECL_AXIS void term_windowing();


} // namespace user





CLASS_DECL_AXIS ::user::interaction * window_from_handle(oswindow oswindow);
CLASS_DECL_AXIS bool oswindow_assign(oswindow oswindow, ::user::interaction * pui);
CLASS_DECL_AXIS bool oswindow_remove(::user::interaction * pui);
