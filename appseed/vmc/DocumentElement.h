#pragma once

#include "Music.h"

class CDocumentElement :
	virtual public CMusic 
{
public:
	enum EType
	{
		InvalidType,
		DocumentBookmark,
		StaffSet,
		Staff,
		Clef,
		TimeSignature,
		KeySignature,
		MusicalVisual,
		NoteSet,
		CoTimeNoteSet,
		Note,
		Rest,
	};

void Serialize(Ex1Archive &ar);

//	virtual void Serialize(CArchive& ar);
	EType GetType(CDocumentElement *pde);
	CDocumentElement * CreateObject(EType etype);
	CDocumentElement * CreateObject(const type_info& ti);
	
	// This class should be the base class for all
	// visual objects or visual helper objects
	// of the document.
	CDocumentElement();
	virtual ~CDocumentElement();

	


};
