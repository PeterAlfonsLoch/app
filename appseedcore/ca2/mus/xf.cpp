#include "StdAfx.h" 
#include "xf.h" 

namespace mus
{

   const BYTE xf::MetaSongName = 0x03;
   const BYTE xf::MetaLyric = 0x05;
   const BYTE xf::MetaXFInfoHdr = 0x01;
   const BYTE xf::MetaLyricsHeader = 0x07;

   xf_lyrics_id::   xf_lyrics_id()
   {
   }
   xf_lyrics_id::~xf_lyrics_id()
   {
   }


   xf_lyrics_id & xf_lyrics_id::operator = (const xf_lyrics_id & xflh)
   {
      m_MelodyTracks       = xflh.m_MelodyTracks;
      m_strLanguage        = xflh.m_strLanguage;
      m_tkDisplayOffset    = xflh.m_tkDisplayOffset;
      return *this;
   }


   xf_lyrics_id::xf_lyrics_id(const xf_lyrics_id & xflh)
   {
      operator = (xflh);
   }

} // namespace mus

