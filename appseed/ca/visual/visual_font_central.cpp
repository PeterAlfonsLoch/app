#include "StdAfx.h"

font_central::font_central(::ca::application * papp) :
   ca(papp),
   m_fontCaption(papp),
   m_fontMenu(papp),
   m_fontStandard(papp),
   m_font(papp),
   m_fontListCtrl(papp)
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

   LOGFONT                 lf;
   memset(&lf, 0, sizeof(lf));
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);
   //lf.lfHeight         = (int)-MulDiv(9, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight = -9;
   lf.lfWeight         = FW_NORMAL;
   lf.lfCharSet        = DEFAULT_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, FONTFACENAME_MENU);

   VERIFY(m_fontMenu->CreateFontIndirect(&lf));

   memset(&lf, 0, sizeof(lf));
   lf.lfHeight         = -(int)11;
   lf.lfWeight         = FW_BOLD;
   lf.lfCharSet        = DEFAULT_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

   m_font->CreatePointFontIndirect(&lf);

   m_fontStandard->CreatePointFont(80, "Lucida Sans Unicode");

   m_pTitleFonts = new primitive_array < visual::font *>;
   m_pSubTitleFonts = new primitive_array < visual::font *>;

   CreateLyricViewFonts();

   NONCLIENTMETRICS ncm;
   memset(&ncm, 0,
   sizeof(ncm));
   ncm.cbSize = sizeof(ncm);
   SystemParametersInfo(
   SPI_GETNONCLIENTMETRICS,
   0, &ncm, 0);
   //get caption bar
   //font handle.
   m_fontCaption->CreateFontIndirect(&ncm.lfCaptionFont);

   memset(&lf, 0, sizeof(lf));
   //lf.lfHeight         = (int)-MulDiv(9, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight = 90;
   lf.lfWeight         = FW_NORMAL;
   lf.lfCharSet        = DEFAULT_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

   VERIFY(m_fontListCtrl->CreateFontIndirect(&lf));

   m_bInitialized = true;
   return true;
}


void font_central::Finalize()
{
   if(!IsInitialized())
      return;

    int i, iSize;



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

::ca::font * font_central::GetStandartFont()
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

::ca::font * font_central::GetMenuFont()
{
    return m_fontMenu;
}

void font_central::CreateLyricViewFonts()
{
   LOGFONT                 lf;

   memset(&lf, 0, sizeof(lf));

   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);

   //lf.lfHeight         = (int)-MulDiv(54, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight = -54;
   lf.lfWeight         = FW_BOLD;
   lf.lfCharSet        = DEFAULT_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

   ::ca::font_sp font(get_app());
   font->CreateFontIndirect(&lf);
   //::ca::font *pFontOld = spgraphics->SelectObject(font);
   //TEXTMETRIC tm;
   //spgraphics->GetTextMetrics(&tm);

   //lf.lfWidth = tm.tmAveCharWidth;
   //lf.lfWidth = 0;
   visual::font * pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();

   //m_pLyricViewFonts->add(pPlayerFont);
   m_pfontLyric = pPlayerFont;

/*   lf.lfWidth = (long) (tm.tmAveCharWidth * 0.90);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewFonts->add(pPlayerFont);

   lf.lfWidth = (long) (tm.tmAveCharWidth * 0.80);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewFonts->add(pPlayerFont);

   lf.lfWidth = (long) (tm.tmAveCharWidth * 0.70);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewFonts->add(pPlayerFont);

   lf.lfWidth = (long) (tm.tmAveCharWidth * 0.60);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewFonts->add(pPlayerFont);*/

   memset(&lf, 0, sizeof(lf));

   //lf.lfHeight         = (int)-MulDiv(12, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight          = -12;
   lf.lfWeight         = FW_BOLD;
   lf.lfCharSet        = ANSI_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Tahoma");

   font->CreateFontIndirect(&lf);
   spgraphics->SelectObject(font);
//   spgraphics->GetTextMetrics(&tm);

   //lf.lfWidth = tm.tmAveCharWidth;
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   //m_pLyricViewCompactFonts->add(pPlayerFont);
   m_pfontLyricCompact = pPlayerFont;

   /*lf.lfWidth = (long) (tm.tmAveCharWidth * 0.90);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewCompactFonts->add(pPlayerFont);

   lf.lfWidth = (long) (tm.tmAveCharWidth * 0.80);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewCompactFonts->add(pPlayerFont);

   lf.lfWidth = (long) (tm.tmAveCharWidth * 0.70);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewCompactFonts->add(pPlayerFont);

   lf.lfWidth = (long) (tm.tmAveCharWidth * 0.60);
   spfont.create(get_app());
   spfont->CreateFontIndirect(&lf);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->SetFont(spfont.detach());
   m_pLyricViewCompactFonts->add(pPlayerFont);*/

   memset(&lf, 0, sizeof(lf));

//   lf.lfHeight         = (int)-MulDiv(48, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight = -48;
   lf.lfWidth         = 0;
   lf.lfWeight         = FW_BOLD;
   lf.lfCharSet        = DEFAULT_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

   font->CreateFontIndirect(&lf);
   spgraphics->SelectObject(font);
//   spgraphics->GetTextMetrics(&tm);

  // lf.lfWidth = tm.tmAveCharWidth;
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   lf.lfWidth = (LONG) (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   lf.lfWidth = (LONG) (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   lf.lfWidth = (LONG) (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   lf.lfWidth = (LONG) (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pTitleFonts->add(pPlayerFont);

   memset(&lf, 0, sizeof(lf));
//   ::ca::graphics * pgraphics = GetDC();
//   pgraphics->SetMapMode(MM_TEXT);
//   RECT rect;
//   GetClientRect(&rect);
    //lf.lfHeight         = (int)-MulDiv(24, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight = -24;
   lf.lfWidth         = 0;
   lf.lfWeight         = FW_NORMAL;
    lf.lfCharSet        = DEFAULT_CHARSET;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = PROOF_QUALITY;
    lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
    lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

   font->CreateFontIndirect(&lf);
   spgraphics->SelectObject(font);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   lf.lfWidth = long (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   lf.lfWidth = long (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   lf.lfWidth = long (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   lf.lfWidth = long (lf.lfWidth * 0.90);
   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pSubTitleFonts->add(pPlayerFont);

   //lf.lfHeight         = (int)-MulDiv(12, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight = -12;
   lf.lfWeight         = FW_BOLD;
   lf.lfCharSet        = DEFAULT_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

   font->CreateFontIndirect(&lf);
   spgraphics->SelectObject(font);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_lpSongLabelFont = pPlayerFont;

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_lpSongListFont = pPlayerFont;


   //lf.lfHeight         = (int)-MulDiv(10, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfHeight = -10;
   lf.lfWeight         = FW_NORMAL;
   lf.lfCharSet        = DEFAULT_CHARSET;
   lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
   lf.lfQuality        = PROOF_QUALITY;
   lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
   lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

   font->CreateFontIndirect(&lf);

   pPlayerFont = new visual::font(get_app());
   pPlayerFont->GetFont()->CreateFontIndirect(&lf);
   pPlayerFont->OnSetFont();
   m_pxffontMidiTrackName = pPlayerFont;


   spgraphics->DeleteDC();

}

::ca::font * font_central::GetCaptionFont()
{
   return m_fontCaption;
}

::ca::font * font_central::GetListCtrlFont()
{
   return m_fontListCtrl;
}
