// LyricViewLineTemplate.h: interface for the CLyricViewLineTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICVIEWLINETEMPLATE_H__AF7246A6_7BB5_4C98_91A7_808A7E9A712F__INCLUDED_)
#define AFX_LYRICVIEWLINETEMPLATE_H__AF7246A6_7BB5_4C98_91A7_808A7E9A712F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLyricViewLineTemplates;

class CLyricViewLineTemplate  
{
    friend class CLyricViewLineTemplates;
public:
	CLyricViewLineTemplate();
	virtual ~CLyricViewLineTemplate();

    enum TextOffsetMode
    {
        tomClip,
        tomNoClip
    };

public:
	void SetPlacement_(LPRECT lpRect);
	void GetColors(COLORREF & crLeft, COLORREF & crRight);
	void GetPens(CPen ** pppenLeft, CPen ** pppenRight);
	void GetMargin(SIZE * lpSize);
	void GetPlacement_(LPRECT lpRect);
    int SetPens(CPen * ppenLeft, CPen * ppenRight);
    int SetColors(COLORREF crLeft, COLORREF crRight);

protected:
    CPen *              m_ppenLeft;
    CPen *              m_ppenRight;
    COLORREF            m_crLeft;
    COLORREF            m_crRight;
    class rect               m_rectPlacement;
    class size               m_sizeMargin;
    CLyricViewLineTemplates * m_pContainer;
    
public:
    class point              m_ptTextOffset;
    enum TextOffsetMode m_etom;
	CLyricViewLineTemplates * GetContainer();
    bool                m_bFirstLine;
    bool                m_bNeedFullUpdate;
    
};

#endif // !defined(AFX_LYRICVIEWLINETEMPLATE_H__AF7246A6_7BB5_4C98_91A7_808A7E9A712F__INCLUDED_)
