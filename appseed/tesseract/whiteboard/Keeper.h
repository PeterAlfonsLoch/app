// Keeper.h: interface for the Keeper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEEPER_H__7C1412C1_E66E_46C0_873E_D4F81AF3206D__INCLUDED_)
#define AFX_KEEPER_H__7C1412C1_E66E_46C0_873E_D4F81AF3206D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class TYPE> class Keeper  
{
public:
	Keeper(TYPE * pKept, TYPE keepValue, TYPE keepAwayValue, bool bStartKept);
	virtual ~Keeper();

    void Keep();
    void KeepAway();

    TYPE    m_keepValue;
    TYPE    m_keepAwayValue;
    TYPE *  m_pKept;
    bool    m_bKept;

};

template <class TYPE>
Keeper<TYPE>::Keeper
    (TYPE * pKept, TYPE keepValue, TYPE keepAwayValue, bool bStartKept)
    :
m_pKept(pKept),
m_keepValue(keepValue),
m_keepAwayValue(keepAwayValue)
{
    if(bStartKept)
    {
        m_bKept = false;
        Keep();
    }
    else
    {
        m_bKept = true;
        KeepAway();
    }
    
}
template <class TYPE>
Keeper<TYPE>::~Keeper()
{
	if(m_bKept)
	{
		KeepAway();
	}
}

template <class TYPE>
void Keeper<TYPE>::Keep()
{
    if(m_pKept)
    {
        *m_pKept = m_keepValue;
        m_bKept = true;
    }
}

template <class TYPE>
void Keeper<TYPE>::KeepAway()
{
    if(m_pKept)
    {
        *m_pKept = m_keepAwayValue;
        m_bKept = false;
    }
}

#endif // !defined(AFX_KEEPER_H__7C1412C1_E66E_46C0_873E_D4F81AF3206D__INCLUDED_)
