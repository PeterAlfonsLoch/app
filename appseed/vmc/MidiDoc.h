#pragma once

#include "mus/MidiDocHelper.h"

class CMidiPlayer;

class CMidiDoc :
	public Document,
   public MidiDocHelper,
	public DBInterface,
	public MidiPlayerInterface

{
public:
   CMidiDoc(::ca::application * papp);

// Attributes
public:
	bool m_bOpening;
	MidiPlayer	*		m_pMidiPlayer;
protected:
   int m_iTargetFileType;
   int m_iFileType;
public:
   BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace);
    BOOL OnSaveDocument(LPCTSTR lpszPathName);

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual ~CMidiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};
