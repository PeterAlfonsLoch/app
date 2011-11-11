// Star350InfoHeader.h: interface for the Star350InfoHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAR350INFOHEADER_H__162C941F_9C70_4622_B61B_90CF4523C18C__INCLUDED_)
#define AFX_STAR350INFOHEADER_H__162C941F_9C70_4622_B61B_90CF4523C18C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class XFInfoHeader;

class CLASS_DECL_ca Star350InfoHeader  
{
public:
   Star350InfoHeader();
   virtual ~Star350InfoHeader();

   string     m_strSongTitle;
   string     m_strLyricsBy;
   string     m_strComposer;
   string     m_strSinger;
   string     m_strMidiBy;
   string     m_strLyricsSync;
   string     m_strDescription;
   string     m_strKeywords;

public:
   VMSRESULT ToXFInfoHeader(XFInfoHeader * pxfih);
   VMSRESULT FromStorage(LPBYTE lpbData, LPBYTE * lpbEnd);


};

#endif // !defined(AFX_STAR350INFOHEADER_H__162C941F_9C70_4622_B61B_90CF4523C18C__INCLUDED_)
