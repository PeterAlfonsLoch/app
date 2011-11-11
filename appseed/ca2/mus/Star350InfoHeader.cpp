#include "StdAfx.h"

Star350InfoHeader::Star350InfoHeader()
{

}

Star350InfoHeader::~Star350InfoHeader()
{

}

VMSRESULT Star350InfoHeader::FromStorage(LPBYTE lpbData, LPBYTE * lpbEnd)
{
    LPBYTE lpbImage = lpbData;
    
    gen::str::copy(m_strSongTitle, (const char *) lpbImage, 48);

    lpbImage += 48;
    gen::str::copy(m_strLyricsBy, (const char *) lpbImage, 32);

    lpbImage += 32;
    gen::str::copy(m_strComposer, (const char *) lpbImage, 32);

    lpbImage += 32;
    gen::str::copy(m_strSinger, (const char *) lpbImage, 32);

    lpbImage += 32;
    gen::str::copy(m_strMidiBy, (const char *) lpbImage, 32);

    lpbImage += 32;
    gen::str::copy(m_strLyricsSync, (const char *) lpbImage, 32);

    lpbImage += 32;
    gen::str::copy(m_strDescription, (const char *) lpbImage, 32);

    lpbImage += 32;
    lpbImage += 33;
    int iCount = *(int *)lpbImage;

    lpbImage += 4;
    gen::str::copy(m_strKeywords, (const char *) lpbImage, iCount);

    lpbImage += iCount;
    *lpbEnd = lpbImage;

    return VMSR_SUCCESS;

}

VMSRESULT Star350InfoHeader::ToXFInfoHeader(XFInfoHeader *pxfih)
{
   ASSERT(pxfih != NULL);

   pxfih->Empty();

   pxfih->m_straComposer.add_tokens(m_strComposer,"/", FALSE);
   pxfih->m_straLyricist.add_tokens(m_strLyricsBy,"/", FALSE);
   pxfih->m_straArranger.add_tokens("","/", FALSE);
   pxfih->m_straPerformer.add_tokens(m_strSinger,"/", FALSE);
   pxfih->m_straProgrammer.add_tokens(m_strMidiBy +"/" + m_strLyricsSync,"/", FALSE);
   pxfih->m_straKeyword.add_tokens(m_strKeywords,"/", FALSE); 

   return VMSR_SUCCESS;
}
