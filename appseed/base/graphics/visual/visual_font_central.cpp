#include "framework.h"

font_central::font_central(sp(::axis::application) papp) :
   element(papp),
   m_fontCaption(allocer()),
   m_fontMenu(allocer()),
   m_fontStandard(allocer()),
   m_font(allocer()),
   m_fontListCtrl(allocer())
{
   m_pfontLyric = NULL;
   m_pfontLyricCompact = NULL;
   m_bInitialized = false;
}

font_central::~font_central()
{
    if(m_lpSongLabelFont != NULL)
        delete m_lpSongLabelFont;

    if(m_lpSongListFont  != NULL)
        delete m_lpSongListFont;

}

//#define FONTFACENAME_MENU "Lucida Sans Unicode"
#define FONTFACENAME_MENU "Arial Unicode"
#ifdef LINUX
#define FONTFACENAME_LUCIDA "sans-serif"
#else
#define FONTFACENAME_LUCIDA "Lucida Sans Unicode"
#endif

bool font_central::IsInitialized()
{
   if(this == NULL)
      return false;
   else
      return m_bInitialized;
}

bool font_central::Initialize()
{

   if(IsInitialized())
      return false;

   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateCompatibleDC(NULL);

   m_fontMenu->create_point_font(FONTFACENAME_MENU, 9);

   m_font->create_point_font(FONTFACENAME_LUCIDA, 11, FW_BOLD);

   m_fontStandard->create_point_font(FONTFACENAME_LUCIDA, 8);

   m_pTitleFonts = new primitive_array < visual::font *>;
   m_pSubTitleFonts = new primitive_array < visual::font *>;

   CreateLyricViewFonts();


   m_fontCaption->create_point_font(FONTFACENAME_LUCIDA, 11);


   m_fontListCtrl->create_point_font(FONTFACENAME_LUCIDA, 9);

   m_bInitialized = true;

   return true;

}


void font_central::Finalize()
{

   if(!IsInitialized())
      return;

   index i;
   ::count iSize;



   delete m_pfontLyric;
   delete m_pfontLyricCompact;

   iSize = m_pTitleFonts->get_size();
   for(i = 0; i < iSize; i++)
   {
      delete m_pTitleFonts->operator[](i);
   }
   delete m_pTitleFonts;

   iSize = m_pSubTitleFonts->get_size();
   for(i = 0; i < iSize; i++)
   {
      delete m_pSubTitleFonts->operator[](i);

   }

   delete m_pSubTitleFonts;

   m_bInitialized = false;

}


::draw2d::font * font_central::GetStandartFont()
{
    return m_fontMenu;
}

//primitive_array < visual::font *> *
//   font_central::GetLyricViewFonts_()
//{
//   return m_pLyricViewFonts;

//}

//primitive_array < visual::font *> *
//   font_central::GetLyricViewCompactFonts_()
//{
//   return m_pLyricViewCompactFonts;
//}

visual::font *
   font_central::GetLyricViewFont()
{
   return m_pfontLyric;
}

visual::font *
   font_central::GetLyricViewCompactFont()
{
   return m_pfontLyricCompact;
}

primitive_array < visual::font *> *
   font_central::GetTitleFonts()
{
   return m_pTitleFonts;
}

primitive_array < visual::font *> *
   font_central::GetSubTitleFonts()
{
   return m_pSubTitleFonts;
}


visual::font * font_central::GetTitleFont()
{
    return m_pTitleFonts->element_at(0);
}

visual::font * font_central::GetSubTitleFont()
{
    return m_pSubTitleFonts->element_at(0);
}

visual::font * font_central::GetMidiTrackNameFont()
{
    return m_pxffontMidiTrackName;
}

visual::font * font_central::GetSongLabelFont()
{
    return m_lpSongLabelFont;
}

visual::font * font_central::GetSongListFont()
{
    return m_lpSongListFont;
}

::draw2d::font * font_central::GetMenuFont()
{
    return m_fontMenu;
}

void font_central::CreateLyricViewFonts()
{
   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateCompatibleDC(NULL);


   string strLucida;


   visual::font * pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 54, FW_BOLD);
   pPlayerFont->OnSetFont();
   m_pfontLyric = pPlayerFont;

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font("Tahoma", 12, FW_BOLD);
   pPlayerFont->OnSetFont();
   m_pfontLyricCompact = pPlayerFont;


   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 48, FW_BOLD);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 48, FW_BOLD, false, false, false, 0.9);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 48, FW_BOLD, false, false, false, 0.9 * 0.9);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 48, FW_BOLD, false, false, false, 0.9 * 0.9 * 0.9);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 48, FW_BOLD, false, false, false, 0.9 * 0.9 * 0.9 * 0.9);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 24, FW_NORMAL);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 24, FW_NORMAL, false, false, false, 0.9);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 24, FW_NORMAL, false, false, false, 0.9 * 0.9);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 24, FW_NORMAL, false, false, false, 0.9 * 0.9 * 0.9);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 24, FW_NORMAL, false, false, false, 0.9 * 0.9 * 0.9 * 0.9);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 12, FW_BOLD);
   pPlayerFont->OnSetFont();
   m_lpSongLabelFont = pPlayerFont;

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 12, FW_BOLD);
   pPlayerFont->OnSetFont();
   m_lpSongListFont = pPlayerFont;



   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->create_point_font(FONTFACENAME_LUCIDA, 10, FW_NORMAL);
   pPlayerFont->OnSetFont();
   m_pxffontMidiTrackName = pPlayerFont;


   spgraphics->DeleteDC();

}

::draw2d::font * font_central::GetCaptionFont()
{
   return m_fontCaption;
}

::draw2d::font * font_central::GetListCtrlFont()
{
   return m_fontListCtrl;
}
