// DocumentElement.cpp: implementation of the CDocumentElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DocumentElement.h"

#include "DocumentBookmark.h"
#include "DEStaffSet.h"
#include "DEStaff.h"
#include "DEClef.h"
#include "DEKeySignature.h"
#include "DETimeSignature.h"
#include "DENoteSet.h"
#include "DECoTimeNoteSet.h"
#include "DENote.h"
#include "DERest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDocumentElement::CDocumentElement()
{

}

CDocumentElement::~CDocumentElement()
{

}

CDocumentElement * CDocumentElement::CreateObject(const type_info &ti)
{
	CDocumentElement * pde;
	if(ti == typeid(CDocumentBookmark))
	{
		pde = (CDocumentElement *) new CDocumentBookmark();
	}
	else if(ti == typeid(CDEStaffSet))
	{
		pde = (CDocumentElement *) new CDEStaffSet();
	}
	else if(ti == typeid(CDEStaff))
	{
		pde = (CDocumentElement *) new CDEStaff();
	}
	else if(ti == typeid(CDEClef))
	{
		pde = (CDocumentElement *) new CDEClef();
	}
	else if(ti == typeid(CDETimeSignature))
	{
		pde = (CDocumentElement *) new CDETimeSignature();
	}
	else if(ti == typeid(CDEKeySignature))
	{
		pde = (CDocumentElement *) new CDEKeySignature();
	}
	else if(ti == typeid(CDENoteSet))
	{
		pde = (CDocumentElement *) new CDENoteSet();
	}
	else if(ti == typeid(CDECoTimeNoteSet))
	{
		pde = (CDocumentElement *) new CDECoTimeNoteSet();
	}
	else if(ti == typeid(CDENote))
	{
		pde = (CDocumentElement *) new CDENote();
	}
	else if(ti == typeid(CDERest))
	{
		pde = (CDocumentElement *) new CDERest();
	}
	else
	{
		pde = NULL;
	}
	return pde;

}

CDocumentElement * CDocumentElement::CreateObject(EType etype)
{
	CDocumentElement * pde;
	switch(etype)
	{
	case DocumentBookmark:
		pde = (CDocumentElement *) new CDocumentBookmark();
		break;
	case StaffSet:
		pde = (CDocumentElement *) new CDEStaffSet();
		break;
	case Staff:
		pde = (CDocumentElement *) new CDEStaff();
		break;
	case Clef:
		pde = (CDocumentElement *) new CDEClef();
		break;
	case TimeSignature:
		pde = (CDocumentElement *) new CDETimeSignature();
		break;
	case KeySignature:
		pde = (CDocumentElement *) new CDEKeySignature();
		break;
	case NoteSet:
		pde = (CDocumentElement *) new CDENoteSet();
		break;
	case CoTimeNoteSet:
		pde = (CDocumentElement *) new CDECoTimeNoteSet();
		break;
	case Note:
		pde = (CDocumentElement *) new CDENote();
		break;
	case Rest:
		pde = (CDocumentElement *) new CDERest();
		break;
	default:
		pde = NULL;
		break;
	}
	return pde;

}

CDocumentElement::EType CDocumentElement::GetType(CDocumentElement *pde)
{
	EType etype;
	if(typeid(pde) == typeid(CDocumentBookmark*))
	{
		etype = DocumentBookmark;
	}
	else if(typeid(pde) == typeid(CDEStaffSet*))
	{
		etype = StaffSet;
	}
	else if(typeid(pde) == typeid(CDEStaff*))
	{
		etype = Staff;
	}
	else if(typeid(pde) == typeid(CDEClef*))
	{
		etype = Clef;
	}
	else if(typeid(pde) == typeid(CDETimeSignature*))
	{
		etype = TimeSignature;
	}
	else if(typeid(pde) == typeid(CDEKeySignature*))
	{
		etype = KeySignature;
	}
	else if(typeid(pde) == typeid(CDENoteSet*))
	{
		etype = NoteSet;
	}
	else if(typeid(pde) == typeid(CDECoTimeNoteSet*))
	{
		etype = CoTimeNoteSet;
	}
	else if(typeid(pde) == typeid(CDENote*))
	{
		etype = Note;
	}
	else if(typeid(pde) == typeid(CDERest*))
	{
		etype = Rest;
	}
	else
	{
		etype = InvalidType;
	}
	return etype;


}

void CDocumentElement::Serialize(Ex1Archive &ar)
{
	EType etype = GetType(this);
	if(ar.IsStoring())
	{
		ar << (int) etype;
	}

}
