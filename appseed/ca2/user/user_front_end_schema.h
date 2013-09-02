#pragma once

namespace user
{

   class button;

   class CLASS_DECL_ca2 front_end_schema :
      virtual public object
   {
   public:

      class button;

      class CLASS_DECL_ca2 system_menu
      {
      public:
         system_menu(sp(::application) papp);
         ::draw2d::font_sp    m_fontMarlett;
      };

      class CLASS_DECL_ca2 menu
      {
      public:
         menu(sp(::application) papp);
         ~menu();
         ::draw2d::font_sp     m_font;
         button *          m_pschemaSysMenuButton;
         button *          m_pschemaItemButton;
         button *          m_pschemaPopupButton;
      };

      class CLASS_DECL_ca2 button
      {
      public:
         button(sp(::application) papp);
         COLORREF          m_crTextNormal;
         COLORREF          m_crTextHover;
         COLORREF          m_crTextPress;
         COLORREF          m_crTextDisabled;
         COLORREF          m_crBkNormal;
         COLORREF          m_crBkHover;
         COLORREF          m_crBkPress;
         COLORREF          m_crBkDisabled;
         ::draw2d::font_sp     m_font;
         bool              m_bBorder;
      };

      menu           m_menu;
      system_menu    m_sysmenu;
      button         m_button;
      button         m_buttonBaseWndMenuSysMenu;
      button         m_buttonBaseWndMenuItem;
      button         m_buttonBaseWndMenuItemPopup;
      COLORREF       m_crTextNormal;
      

      front_end_schema(sp(::application) app);
      ~front_end_schema();

      virtual void DrawCheck(check::check echeck, LPCRECT lpcrect, ::draw2d::graphics * pdc);

      

   };

} // namespace user