#pragma once

namespace user
{

   class button;

   class CLASS_DECL_ca front_end_schema
   {
   public:

      class button;

      class CLASS_DECL_ca system_menu
      {
      public:
         system_menu(::ax::application * papp);
         ::ax::font_sp    m_fontMarlett;
      };

      class CLASS_DECL_ca menu
      {
      public:
         menu(::ax::application * papp);
         ~menu();
         ::ax::font_sp     m_font;
         button *          m_pschemaSysMenuButton;
         button *          m_pschemaItemButton;
         button *          m_pschemaPopupButton;
      };

      class CLASS_DECL_ca button
      {
      public:
         button(::ax::application * papp);
         COLORREF          m_crTextNormal;
         COLORREF          m_crTextHover;
         COLORREF          m_crTextPress;
         COLORREF          m_crTextDisabled;
         COLORREF          m_crBkNormal;
         COLORREF          m_crBkHover;
         COLORREF          m_crBkPress;
         COLORREF          m_crBkDisabled;
         ::ax::font_sp     m_font;
         bool              m_bBorder;
      };

      menu           m_menu;
      system_menu    m_sysmenu;
      button         m_button;
      button         m_buttonBaseWndMenuSysMenu;
      button         m_buttonBaseWndMenuItem;
      button         m_buttonBaseWndMenuItemPopup;
      

      front_end_schema(::ax::application * app);
      ~front_end_schema(void);

      virtual void DrawCheck(check::check echeck, LPCRECT lpcrect, ::ax::graphics * pdc);

      

   };

} // namespace user