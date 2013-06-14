#pragma once

class CXfplayerSong;

namespace visual
{
   class font;
}

typedef primitive_array < visual::font * > CVmsGdiFontPtrArray;

class CLASS_DECL_ca2 font_central :
   virtual public ::ca2::object
{
public:
   font_central(sp(::ca2::application) papp);
   virtual ~font_central();

protected:
   ::ca2::font_sp           m_fontCaption;
   ::ca2::font_sp           m_fontMenu;
   ::ca2::font_sp           m_fontStandard;
   ::ca2::font_sp           m_font;
   ::ca2::font_sp           m_fontListCtrl;
   visual::font *               m_lpSongLabelFont;
   visual::font *             m_lpSongListFont;
   visual::font *             m_pfontLyric;
   visual::font *             m_pfontLyricCompact;
   visual::font *             m_pxffontMidiTrackName;
   CVmsGdiFontPtrArray *   m_pTitleFonts;
   CVmsGdiFontPtrArray *   m_pSubTitleFonts;
   bool                    m_bInitialized;
public:
   ::ca2::font * GetListCtrlFont();
   ::ca2::font * GetCaptionFont();
   ::ca2::font * GetStandartFont();
   void Finalize();
   bool Initialize();
   visual::font * GetSongListFont();
   visual::font * GetSongLabelFont();
   visual::font * GetTitleFont();
   visual::font * GetSubTitleFont();
   visual::font * GetMidiTrackNameFont();
   ::ca2::font * GetMenuFont();
   void CreateLyricViewFonts();
   visual::font * GetLyricViewFont();
   visual::font * GetLyricViewCompactFont();
   CVmsGdiFontPtrArray * GetTitleFonts();
   CVmsGdiFontPtrArray * GetSubTitleFonts();

   bool IsInitialized();
};

