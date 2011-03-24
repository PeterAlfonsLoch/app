#pragma once

//   Extra SMF and XF Format
class CLASS_DECL_ca CXF
{
public:
   static const BYTE MetaSongName;
   static const BYTE MetaLyric;
   static const BYTE MetaXFInfoHdr;
   static const BYTE MetaLyricsHeader;
   
   UINT SymbolCharCodeToCodePage(string &strSymbol)
   {
      if(strSymbol.CompareNoCase("L1") == 0)
      {
         return 1252;
      }
      if(strSymbol.CompareNoCase("JP") == 0)
      {
         return 932;
      }
      else
      {
         return 1252;
      }
   }

};
//#define   MIDI_META_LYRICS               ((BYTE)0x05)
//#define   MIDI_META_SONG_NAME               ((BYTE)0x03)
//#define   MIDI_META_XF_INFORMATION_HEADER      ((BYTE)0x01)
//#define   MIDI_META_XF_LYRICS_HEADER         ((BYTE)0x07)

#define XFPLYR_BREAK_LINE_FEED 1

//  XfplayerViewLine constants


//#define   XFPLYR_LINE_STATUS_EMPTY 1
//#define   XFPLYR_LINE_STATUS_NEW 2
//#define   XFPLYR_LINE_STATUS_PLAYING 3
//#define   XFPLYR_LINE_STATUS_PLAYED 4

//#define   XFPLYR_LINE_RENDER_CLEAR_FULL 1
//#define   XFPLYR_LINE_RENDER_UPDATE 2
//#define   XFPLYR_LINE_RENDER_CLEAR 3
//#define   XFPLYR_LINE_RENDER_FULL 4

//#define XFPLYR_LINE_ERROR_OUT_OF_BOUND -4
//#define XFPLYR_LINE_RESULT int

//#define XF_OPEN_FOR_PLAYING 1
//#define XF_OPEN_FOR_PARSING 2


/*class XFInfoHeader
{
public:
   string ID;
   string Date;
   string Country;
   string   Category;
   string Beat;
   string   MelodyInstrument;
   string VocalType;
   string Composer;
   string Lyricist;
   string Arranger;
   string Performer;
   string Programmer;
   string Keyword;
};*/

/*class XFInfoHeaderLS
{
public:
   string ID;
   string Language;
   string SongName;
   string Composer;
   string Lyricist;
   string Arranger;
   string Performer;
   string Programmer;
   string Keyword;
}; */

class CLASS_DECL_ca XFVersionID
{
public:
   BYTE m_hpbImage[9];
};

class CLASS_DECL_ca XFLyricsHeader
{
public:
   XFLyricsHeader();
   XFLyricsHeader(const XFLyricsHeader & xflh);
   virtual ~XFLyricsHeader();
   dword_array    m_MelodyTracks;
   imedia::position            m_tkDisplayOffset;
   string         m_strLanguage;

   XFLyricsHeader & operator =(const XFLyricsHeader &xflh);
};

