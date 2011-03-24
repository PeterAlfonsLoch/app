// SynchEditorViewUpdateHint.h: interface for the CSynchEditorViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCHEDITORVIEWUPDATEHINT_H__F4BD55A7_8C57_49AD_B169_3C8AC5A82786__INCLUDED_)
#define AFX_SYNCHEDITORVIEWUPDATEHINT_H__F4BD55A7_8C57_49AD_B169_3C8AC5A82786__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSynchEditorViewUpdateHint 
   :
   public CObject
{
   DECLARE_DYNAMIC(CSynchEditorViewUpdateHint)
public:
	CSynchEditorViewUpdateHint();
	virtual ~CSynchEditorViewUpdateHint();

   enum EType
   {
      TypeConfigIdUpdate,
   };

   EType    m_etype;
   int      m_iConfigId;

};

#endif // !defined(AFX_SYNCHEDITORVIEWUPDATEHINT_H__F4BD55A7_8C57_49AD_B169_3C8AC5A82786__INCLUDED_)
