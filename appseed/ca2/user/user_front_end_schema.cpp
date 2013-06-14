#include "framework.h"


namespace user
{


   front_end_schema::front_end_schema(sp(::ca2::application) papp) :
      ca2(papp),
      m_menu(papp),
      m_sysmenu(papp),
      m_button(papp),
      m_buttonBaseWndMenuSysMenu(papp),
      m_buttonBaseWndMenuItem(papp),
      m_buttonBaseWndMenuItemPopup(papp)
   {

      ::ca2::graphics_sp spgraphics(papp->allocer());
      spgraphics->CreateCompatibleDC(NULL);

      m_button.m_font->create_point_font("Arial", 11.0);


      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));

      class color colorHover(color);
      colorHover.hls_rate(0.0, 0.3, 0.0);

      class color colorPress(color);
      colorHover.hls_rate(0.0, 0.7, 0.0);


      m_button.m_crTextNormal          = ARGB(255, 0, 0, 0);
      m_button.m_crTextHover           = color | (0xff << 24);
      m_button.m_crTextNormal          = ARGB(255, 0, 0, 0);
      m_button.m_crBkNormal            = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);
      m_button.m_crBkPress             = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);
      m_button.m_crBkDisabled          = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);
      m_button.m_crBkHover             = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);


      m_buttonBaseWndMenuSysMenu.m_font->create_point_font("Marlett", 11.0);


      m_buttonBaseWndMenuSysMenu.m_crTextNormal          = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuSysMenu.m_crTextHover           = color | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crTextNormal          = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuSysMenu.m_crBkNormal            = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crBkPress             = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crBkDisabled          = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crBkHover             = Session.get_default_color(COLOR_3DFACE) | (0xff << 24);


      m_buttonBaseWndMenuItem.m_font->create_point_font("Lucida Sans Unicode", 9.0);

      m_buttonBaseWndMenuItem.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuItem.m_crTextHover  = color | (0xff << 24);
      m_buttonBaseWndMenuItem.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuSysMenu.m_crBkNormal    = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);        
      m_buttonBaseWndMenuSysMenu.m_crBkPress  = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);           
      m_buttonBaseWndMenuSysMenu.m_crBkDisabled    = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);      
      m_buttonBaseWndMenuSysMenu.m_crBkHover     = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);        

      //m_buttonBaseWndMenuItem.m_crBk         = Session.get_default_color(COLOR_3DHIGHLIGHT);
      m_buttonBaseWndMenuItem.m_crTextDisabled = RGB(127, 127, 127) | (0xff << 24);
      m_buttonBaseWndMenuItem.m_bBorder      = false;



      m_menu.m_font->create_point_font("Lucida Sans Unicode", 9.0);




      m_buttonBaseWndMenuItemPopup.m_font->create_point_font( "Lucida Sans Unicode", 9.0, FW_BOLD);

      m_buttonBaseWndMenuItemPopup.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuItemPopup.m_crTextHover  = color | (0xff << 24);
      m_buttonBaseWndMenuItemPopup.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuItemPopup.m_crBkNormal    = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);        
      m_buttonBaseWndMenuItemPopup.m_crBkPress  = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);           
      m_buttonBaseWndMenuItemPopup.m_crBkDisabled    = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);      
      m_buttonBaseWndMenuItemPopup.m_crBkHover     = Session.get_default_color(COLOR_3DHIGHLIGHT) | (0xff << 24);        
      m_buttonBaseWndMenuItemPopup.m_crTextDisabled = ARGB(255, 127, 127, 127);
      m_buttonBaseWndMenuItemPopup.m_bBorder      = false;



      m_menu.m_pschemaSysMenuButton = &m_buttonBaseWndMenuSysMenu;
      m_menu.m_pschemaItemButton = &m_buttonBaseWndMenuItem;
      m_menu.m_pschemaPopupButton = &m_buttonBaseWndMenuItemPopup;




   }

   front_end_schema::~front_end_schema()
   {
   }

   front_end_schema::system_menu::system_menu(sp(::ca2::application) papp) :
      m_fontMarlett(papp->allocer())
   {
      ::ca2::graphics_sp spgraphics(papp->allocer());
      spgraphics->CreateCompatibleDC(NULL);

      m_fontMarlett->create_point_font("Marlett", 11.0);
   }

   front_end_schema::menu::menu(sp(::ca2::application) papp) :
      m_font(papp->allocer())
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

   void front_end_schema::DrawCheck(check::check echeck, LPCRECT lpcrect, ::ca2::graphics * pdc)
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

         pta.offset(lpcrect->left, lpcrect->top);

         pdc->Polygon(pta);

      }

   }

   front_end_schema::button::button(sp(::ca2::application) papp) :
      m_font(papp->allocer())
   {
      m_bBorder = true;
   }


} // namespace ca2



