#include "StdAfx.h" 
#include "Xf.h" 

const BYTE CXF::MetaSongName = 0x03;
const BYTE CXF::MetaLyric = 0x05;
const BYTE CXF::MetaXFInfoHdr = 0x01;
const BYTE CXF::MetaLyricsHeader = 0x07;

XFLyricsHeader::   XFLyricsHeader()
{
}
XFLyricsHeader::~XFLyricsHeader()
{
}


XFLyricsHeader & XFLyricsHeader::operator = (const XFLyricsHeader & xflh)
{
   m_MelodyTracks       = xflh.m_MelodyTracks;
   m_strLanguage        = xflh.m_strLanguage;
   m_tkDisplayOffset    = xflh.m_tkDisplayOffset;
   return *this;
}


XFLyricsHeader::XFLyricsHeader(const XFLyricsHeader & xflh)
{
   operator = (xflh);
}
