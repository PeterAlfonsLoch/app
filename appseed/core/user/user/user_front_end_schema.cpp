//#include "framework.h"


namespace user
{


   front_end_schema::front_end_schema(::aura::application * papp) :
      object(papp),
      m_menu(papp),
      m_sysmenu(papp),
      m_button(papp),
      m_buttonBaseWndMenuSysMenuClose(papp),
      m_buttonBaseWndMenuSysMenu(papp),
      m_buttonBaseWndMenuItem(papp),
      m_buttonBaseWndMenuItemPopup(papp)
   {




      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));

      class color colorHover(color);
      colorHover.hls_rate(0.0, 0.3, 0.0);

      class color colorPress(color);
      colorHover.hls_rate(0.0, 0.7, 0.0);

      m_button.m_pfont.alloc(allocer());
      m_button.m_pfont->create_point_font("Arial",11.0);
      m_button.set_color(color_text_normal,ARGB(255,0,0,0));
      m_button.set_color(color_text_press,color | (0xff << 24));
      m_button.set_color(color_text_disabled,ARGB(255,127,127,127));
      m_button.set_color(color_text_hover,color | (0xff << 24));
      m_button.set_color(color_background_normal,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      m_button.set_color(color_background_press,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      m_button.set_color(color_background_disabled,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      m_button.set_color(color_background_hover,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      m_button.m_bBorder      = false;
      m_button.m_etranslucency = ::user::TranslucencyNone;

      m_buttonBaseWndMenuSysMenuClose.m_pfont.alloc(allocer());
      m_buttonBaseWndMenuSysMenuClose.m_pfont->create_point_font("Marlett",11.0);
      m_buttonBaseWndMenuSysMenuClose.set_color(color_text_normal,ARGB(184,184,84,77));
      m_buttonBaseWndMenuSysMenuClose.set_color(color_text_press,ARGB(223,255,0,0));
      m_buttonBaseWndMenuSysMenuClose.set_color(color_text_disabled,ARGB(184,127,127,127));
      m_buttonBaseWndMenuSysMenuClose.set_color(color_text_hover,ARGB(184,255,49,49));
      m_buttonBaseWndMenuSysMenuClose.set_color(color_background_normal,ARGB(184,208,192,192));
      m_buttonBaseWndMenuSysMenuClose.set_color(color_background_press,ARGB(223,255,192,192));
      m_buttonBaseWndMenuSysMenuClose.set_color(color_background_disabled,ARGB(184,192,192,192));
      m_buttonBaseWndMenuSysMenuClose.set_color(color_background_hover,ARGB(184,223,192,192));
      m_buttonBaseWndMenuSysMenuClose.m_bBorder      = false;
      m_buttonBaseWndMenuSysMenuClose.m_etranslucency = ::user::TranslucencyPresent;


      m_buttonBaseWndMenuSysMenu.m_pfont.alloc(allocer());
      m_buttonBaseWndMenuSysMenu.m_pfont->create_point_font("Marlett", 11.0);
      m_buttonBaseWndMenuSysMenu.set_color(color_text_normal,ARGB(184,0,0,0));
      m_buttonBaseWndMenuSysMenu.set_color(color_text_press,color | (184 << 24));
      m_buttonBaseWndMenuSysMenu.set_color(color_text_disabled,ARGB(184,127,127,127));
      m_buttonBaseWndMenuSysMenu.set_color(color_text_hover,color | (184 << 24));
      m_buttonBaseWndMenuSysMenu.set_color(color_background_normal,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      m_buttonBaseWndMenuSysMenu.set_color(color_background_press,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      m_buttonBaseWndMenuSysMenu.set_color(color_background_disabled,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      m_buttonBaseWndMenuSysMenu.set_color(color_background_hover,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      m_buttonBaseWndMenuSysMenu.m_bBorder      = false;
      m_buttonBaseWndMenuSysMenu.m_etranslucency = ::user::TranslucencyPresent;


      m_buttonBaseWndMenuItem.m_pfont.alloc(allocer());
      m_buttonBaseWndMenuItem.m_pfont->create_point_font("Lucida Sans Unicode", 9.0);
      m_buttonBaseWndMenuItem.set_color(color_text_normal,ARGB(184,0,0,0));
      m_buttonBaseWndMenuItem.set_color(color_text_press,color | (184 << 24));
      m_buttonBaseWndMenuItem.set_color(color_text_disabled,ARGB(184,127,127,127));
      m_buttonBaseWndMenuItem.set_color(color_text_hover,color | (184 << 24));
      m_buttonBaseWndMenuItem.set_color(color_background_normal,ARGB(84, 180, 192, 255));
      m_buttonBaseWndMenuItem.set_color(color_background_press,ARGB(184,180,192,255));
      m_buttonBaseWndMenuItem.set_color(color_background_disabled,ARGB(84,180,192,255));
      m_buttonBaseWndMenuItem.set_color(color_background_hover,ARGB(127,180,192,255));
      m_buttonBaseWndMenuItem.m_bBorder      = false;
      m_buttonBaseWndMenuItem.m_etranslucency = ::user::TranslucencyPresent;


      



      m_buttonBaseWndMenuItemPopup.m_pfont.alloc(allocer());
      m_buttonBaseWndMenuItemPopup.m_pfont->create_point_font( "Lucida Sans Unicode", 9.0, FW_BOLD);
      m_buttonBaseWndMenuItemPopup.set_color(color_text_normal,ARGB(184,0,0,0));
      m_buttonBaseWndMenuItemPopup.set_color(color_text_press,color | (184 << 24));
      m_buttonBaseWndMenuItemPopup.set_color(color_text_disabled,ARGB(184,127,127,127));
      m_buttonBaseWndMenuItemPopup.set_color(color_text_hover,color | (184 << 24));
      m_buttonBaseWndMenuItemPopup.set_color(color_background_normal, Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      m_buttonBaseWndMenuItemPopup.set_color(color_background_press,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      m_buttonBaseWndMenuItemPopup.set_color(color_background_disabled,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      m_buttonBaseWndMenuItemPopup.set_color(color_background_hover,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      m_buttonBaseWndMenuItemPopup.m_bBorder      = false;
      m_buttonBaseWndMenuItemPopup.m_etranslucency = ::user::TranslucencyPresent;


      m_menu.m_font->create_point_font("Lucida Sans Unicode",9.0);

      m_menu.m_pschemaSysMenuCloseButton = &m_buttonBaseWndMenuSysMenuClose;
      m_menu.m_pschemaSysMenuButton = &m_buttonBaseWndMenuSysMenu;
      m_menu.m_pschemaItemButton = &m_buttonBaseWndMenuItem;
      m_menu.m_pschemaPopupButton = &m_buttonBaseWndMenuItemPopup;


      m_crTextNormal = ARGB(255, 0, 0, 0);

   }

   front_end_schema::~front_end_schema()
   {
   }

   front_end_schema::system_menu::system_menu(::aura::application * papp) :
      m_fontMarlett(papp->m_pcoreapp->allocer())
   {
      ::draw2d::graphics_sp spgraphics(papp->m_pcoreapp->allocer());
      spgraphics->CreateCompatibleDC(NULL);

      m_fontMarlett->create_point_font("Marlett", 11.0);
   }

   front_end_schema::menu::menu(::aura::application * papp) :
      m_font(papp->m_pcoreapp->allocer())
   {
      //m_pschemaSysMenuButton = new button();

   }

   front_end_schema::menu::~menu()
   {
      //if(m_pschemaSysMenuButton != NULL)
      //{
      // delete m_pschemaSysMenuButton;
      //m_pschemaSysMenuButton = NULL;
      //}
   }

   void front_end_schema::DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pdc)
   {
      if(echeck == check::checked)
      {
         point_array pta;

         pta.add(point(2, 10));
         pta.add(point(6, 14));
         pta.add(point(14, 6));
         pta.add(point(14, 2));
         pta.add(point(6, 12));
         pta.add(point(2, 8));

         pta.offset(rect.left, rect.top);

         pdc->Polygon(pta);

      }

   }


   front_end_schema::button::button(::aura::application * papp) :
      object(papp),
      ::user::schema_simple_impl(papp)
   {

      m_bBorder = true;

   }


} // namespace core



