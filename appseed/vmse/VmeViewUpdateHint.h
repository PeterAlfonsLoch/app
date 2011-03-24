// VmeViewUpdateHint.h: interface for the CVmeViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMEVIEWUPDATEHINT_H__5D37247C_5EB2_4211_BF91_EE5BDC8B515F__INCLUDED_)
#define AFX_VMEVIEWUPDATEHINT_H__5D37247C_5EB2_4211_BF91_EE5BDC8B515F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmeViewUpdateHint : public CObject  
{
    DECLARE_DYNAMIC(CVmeViewUpdateHint);
public:
	CVmeViewUpdateHint();
	virtual ~CVmeViewUpdateHint();

    int m_iType;
    HTREEITEM m_htreeitem;


};

#endif // !defined(AFX_VMEVIEWUPDATEHINT_H__5D37247C_5EB2_4211_BF91_EE5BDC8B515F__INCLUDED_)
