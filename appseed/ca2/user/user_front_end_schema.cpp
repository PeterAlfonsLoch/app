#include "framework.h"

namespace user
{

   front_end_schema::front_end_schema(::ca::application * papp) :
     m_menu(papp),
     m_sysmenu(papp),
     m_button(papp),
     m_buttonBaseWndMenuSysMenu(papp),
     m_buttonBaseWndMenuItem(papp),
     m_buttonBaseWndMenuItemPopup(papp)
   {
      ::ca::graphics_sp spgraphics(papp);
      spgraphics->CreateCompatibleDC(NULL);

      LOGFONT lf;

      memset(&lf, 0, sizeof(LOGFONT));


      //lf.lfHeight         = (int)-MulDiv(11, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
      lf.lfHeight         = 11;
      lf.lfWeight         = FW_NORMAL;
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
      lf.lfQuality        = PROOF_QUALITY;
      lf.lfPitchAndFamily = FF_SWISS|DEFAULT_PITCH;
      lstrcpy(lf.lfFaceName, "Arial");

      m_button.m_font->CreateFontIndirect(&lf);

      memset(&lf, 0, sizeof(LOGFONT));

      //lf.lfHeight         = (int)-MulDiv(11, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
      lf.lfHeight         = 11;
      lf.lfWeight         = FW_NORMAL;
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
      lf.lfQuality        = PROOF_QUALITY;
      lf.lfPitchAndFamily = FF_SWISS|DEFAULT_PITCH;
      lstrcpy(lf.lfFaceName, "Marlett");

      m_buttonBaseWndMenuSysMenu.m_font->CreateFontIndirect(&lf);

      color color;
      color.set_rgb(::GetSysColor(COLOR_HIGHLIGHT));
      class color colorHover(color);
      colorHover.hls_rate(0.0, 0.3, 0.0);
      class color colorPress(color);
      colorHover.hls_rate(0.0, 0.7, 0.0);

      m_buttonBaseWndMenuSysMenu.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuSysMenu.m_crTextHover  = color | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuSysMenu.m_crBkNormal            = ::GetSysColor(COLOR_3DFACE) | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crBkPress             = ::GetSysColor(COLOR_3DFACE) | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crBkDisabled          = ::GetSysColor(COLOR_3DFACE) | (0xff << 24);
      m_buttonBaseWndMenuSysMenu.m_crBkHover             = ::GetSysColor(COLOR_3DFACE) | (0xff << 24);

      lf.lfHeight         = 90;
      lf.lfWeight         = FW_NORMAL;
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
      lf.lfQuality        = PROOF_QUALITY;
      lf.lfPitchAndFamily = FF_SWISS|DEFAULT_PITCH;
      lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

      m_buttonBaseWndMenuItem.m_font->CreateFontIndirect(&lf);

      m_buttonBaseWndMenuItem.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuItem.m_crTextHover  = color | (0xff << 24);
      m_buttonBaseWndMenuItem.m_crTextNormal = ARGB(255, 0, 0, 0);
   m_buttonBaseWndMenuSysMenu.m_crBkNormal    = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);        
   m_buttonBaseWndMenuSysMenu.m_crBkPress  = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);           
   m_buttonBaseWndMenuSysMenu.m_crBkDisabled    = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);      
   m_buttonBaseWndMenuSysMenu.m_crBkHover     = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);        

      //m_buttonBaseWndMenuItem.m_crBk         = ::GetSysColor(COLOR_3DHIGHLIGHT);
      m_buttonBaseWndMenuItem.m_crTextDisabled = RGB(127, 127, 127) | (0xff << 24);
      m_buttonBaseWndMenuItem.m_bBorder      = false;


      memset(&lf, 0, sizeof(LOGFONT));


            lf.lfHeight         = 90;

      lf.lfWeight         = FW_NORMAL;
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
      lf.lfQuality        = PROOF_QUALITY;
      lf.lfPitchAndFamily = FF_SWISS|DEFAULT_PITCH;
      lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

      m_menu.m_font->CreateFontIndirect(&lf);

      memset(&lf, 0, sizeof(LOGFONT));



            lf.lfHeight         = 90;

      lf.lfWeight         = 800;
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
      lf.lfQuality        = PROOF_QUALITY;
      lf.lfPitchAndFamily = FF_SWISS|DEFAULT_PITCH;
      lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

      m_buttonBaseWndMenuItemPopup.m_font->CreateFontIndirect(&lf);

      m_buttonBaseWndMenuItemPopup.m_crTextNormal = ARGB(255, 0, 0, 0);
      m_buttonBaseWndMenuItemPopup.m_crTextHover  = color | (0xff << 24);
      m_buttonBaseWndMenuItemPopup.m_crTextNormal = ARGB(255, 0, 0, 0);
    m_buttonBaseWndMenuItemPopup.m_crBkNormal    = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);        
   m_buttonBaseWndMenuItemPopup.m_crBkPress  = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);           
   m_buttonBaseWndMenuItemPopup.m_crBkDisabled    = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);      
   m_buttonBaseWndMenuItemPopup.m_crBkHover     = ::GetSysColor(COLOR_3DHIGHLIGHT) | (0xff << 24);        
     m_buttonBaseWndMenuItemPopup.m_crTextDisabled = ARGB(255, 127, 127, 127);
      m_buttonBaseWndMenuItemPopup.m_bBorder      = false;



      m_menu.m_pschemaSysMenuButton = &m_buttonBaseWndMenuSysMenu;
      m_menu.m_pschemaItemButton = &m_buttonBaseWndMenuItem;
      m_menu.m_pschemaPopupButton = &m_buttonBaseWndMenuItemPopup;


      

   }

   front_end_schema::~front_end_schema()
   {
   }

   front_end_schema::system_menu::system_menu(::ca::application * papp) :
      m_fontMarlett(papp)
   {
      ::ca::graphics_sp spgraphics(papp);
      spgraphics->CreateCompatibleDC(NULL);

      LOGFONT lf;

      memset(&lf, 0, sizeof(LOGFONT));


            lf.lfHeight         = 11;

      lf.lfWeight         = FW_NORMAL;
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
      lf.lfQuality        = PROOF_QUALITY;
      lf.lfPitchAndFamily = FF_SWISS|DEFAULT_PITCH;
      lstrcpy(lf.lfFaceName, "Marlett");

      m_fontMarlett->CreateFontIndirect(&lf);
   }

   front_end_schema::menu::menu(::ca::application * papp) :
      m_font(papp)
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

   void front_end_schema::DrawCheck(check::check echeck, LPCRECT lpcrect, ::ca::graphics * pdc)
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

         visual::visual visual(pdc);
         visual.Polygon(pta);

      }

   }

   front_end_schema::button::button(::ca::application * papp) :
      m_font(papp)
   {
      m_bBorder = true;
   }

} // namespace ex1