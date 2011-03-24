#pragma once

namespace userex
{

   class pane_view;

   class CLASS_DECL_ca pane_tab_view :
      virtual public ::userbase::tab_view,
      virtual public ::user::create_view
   {
   public:
      pane_tab_view(::ca::application * papp);
      virtual ~pane_tab_view();

#if !core_level_1
      using ::userbase::tab_view::create_view;
      using ::user::create_view::create_view;
      using ::userbase::tab_view::get_view_uie;
      using ::user::create_view::get_view_uie;
      using ::user::tab_callback::on_show_view;
#endif
      virtual ::user::interaction* get_view_uie();
      virtual id get_view_id();

      virtual void on_show_view();


      virtual void GetTabClientRect(LPRECT lprect);

      pane_view * m_ppaneview;
   };


} // namespace userex