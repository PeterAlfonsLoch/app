#pragma once

class CXfplayerSong;

namespace visual
{
   class font;
}

typedef primitive_array < visual::font * > CVmsGdiFontPtrArray;

class CLASS_DECL_CORE font_central :
   virtual public ::object
{
public:
   font_central(sp(::base::application) papp);
   virtual ~font_central();

protected:
   ::draw2d::font_sp           m_fontCaption;
   ::draw2d::font_sp           m_fontMenu;
   ::draw2d::font_sp           m_fontStandard;
   ::draw2d::font_sp           m_font;
   ::draw2d::font_sp           m_fontListCtrl;
   visual::font *               m_lpSongLabelFont;
   visual::font *             m_lpSongListFont;
   visual::font *             m_pfontLyric;
   visual::font *             m_pfontLyricCompact;
   visual::font *             m_pxffontMidiTrackName;
   CVmsGdiFontPtrArray *   m_pTitleFonts;
   CVmsGdiFontPtrArray *   m_pSubTitleFonts;
   bool                    m_bInitialized;
public:
   ::draw2d::font * GetListCtrlFont();
   ::draw2d::font * GetCaptionFont();
   ::draw2d::font * GetStandartFont();
   void Finalize();
   bool Initialize();
   visual::font * GetSongListFont();
   visual::font * GetSongLabelFont();
   visual::font * GetTitleFont();
   visual::font * GetSubTitleFont();
   visual::font * GetMidiTrackNameFont();
   ::draw2d::font * GetMenuFont();
   void CreateLyricViewFonts();
   visual::font * GetLyricViewFont();
   visual::font * GetLyricViewCompactFont();
   CVmsGdiFontPtrArray * GetTitleFonts();
   CVmsGdiFontPtrArray * GetSubTitleFonts();

   bool IsInitialized();
};

