// MSNote.h: interface for the CMSNote class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSNOTE_H__C081856C_F468_492E_BF61_453A30292014__INCLUDED_)
#define AFX_MSNOTE_H__C081856C_F468_492E_BF61_453A30292014__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMSNoteUnit
{
public:
	CMSNoteUnit();
	virtual ~CMSNoteUnit();

public:
	void TranslateToShSymbol();
    inline unsigned short GetSymbol();
    inline unsigned short GetPositionX();
    inline short GetPositionY();
    inline unsigned short GetSize();
    inline short GetSymbolDelta();

    inline void SetSymbol(unsigned short ushSymbol);
    inline void SetPositionX(unsigned short ushPositionX);
    inline void SetPositionY(short shPositionY);
    inline void SetSize(unsigned short ushSize);
    inline void SetSymbolDelta(short ushSymbolDelta);

    void SetSymbol(int iSymbol);

protected:
    int             m_iSymbol;
    unsigned short  m_ushSymbol;
    unsigned short  m_ushPositionX;
    short           m_shPositionY;
    unsigned short  m_ushSize;
    short  m_shSymbolDelta;
    
};

inline unsigned short CMSNoteUnit::GetSymbol()
{
    return m_ushSymbol;
}
inline unsigned short CMSNoteUnit::GetPositionX()
{
    return m_ushPositionX;
}
inline short CMSNoteUnit::GetPositionY()
{
    return m_shPositionY;
}
inline unsigned short CMSNoteUnit::GetSize()
{
    return m_ushSize;
}
inline short CMSNoteUnit::GetSymbolDelta()
{
    return m_shSymbolDelta;
}

inline void CMSNoteUnit::SetSymbol(unsigned short ushSymbol)
{
    m_ushSymbol = ushSymbol;
}
inline void CMSNoteUnit::SetPositionX(unsigned short ushPositionX)
{
    m_ushPositionX = ushPositionX;
}
inline void CMSNoteUnit::SetPositionY(short shPositionY)
{
    m_shPositionY = shPositionY;
}
inline void CMSNoteUnit::SetSize(unsigned short ushSize)
{
    m_ushSize = ushSize;
}
inline void CMSNoteUnit::SetSymbolDelta( short ushSymbolDelta)
{
    m_shSymbolDelta = ushSymbolDelta;
}

#endif // !defined(AFX_MSNOTE_H__C081856C_F468_492E_BF61_453A30292014__INCLUDED_)
