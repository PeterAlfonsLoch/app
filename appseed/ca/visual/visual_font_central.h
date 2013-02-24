#pragma once

class CXfplayerSong;

namespace visual
{
   class font;
}

typedef primitive_array < visual::font * > CVmsGdiFontPtrArray;

class CLASS_DECL_ca font_central :
   virtual public ::ca::object
{
public:
   font_central(::ca::application * papp);
   virtual ~font_central();

protected:
   ::ca::font_sp           m_fontCaption;
   ::ca::font_sp           m_fontMenu;
   ::ca::font_sp           m_fontStandard;
   ::ca::font_sp           m_font;
   ::ca::font_sp           m_fontListCtrl;
   visual::font *               m_lpSongLabelFont;
   visual::font *             m_lpSongListFont;
   visual::font *             m_pfontLyric;
   visual::font *             m_pfontLyricCompact;
   visual::font *             m_pxffontMidiTrackName;
   CVmsGdiFontPtrArray *   m_pTitleFonts;
   CVmsGdiFontPtrArray *   m_pSubTitleFonts;
   bool                    m_bInitialized;
public:
   ::ca::font * GetListCtrlFont();
   ::ca::font * GetCaptionFont();
   ::ca::font * GetStandartFont();
   void Finalize();
   bool Initialize();
   visual::font * GetSongListFont();
   visual::font * GetSongLabelFont();
   visual::font * GetTitleFont();
   visual::font * GetSubTitleFont();
   visual::font * GetMidiTrackNameFont();
   ::ca::font * GetMenuFont();
   void CreateLyricViewFonts();
   visual::font * GetLyricViewFont();
   visual::font * GetLyricViewCompactFont();
   CVmsGdiFontPtrArray * GetTitleFonts();
   CVmsGdiFontPtrArray * GetSubTitleFonts();

   bool IsInitialized();
};

