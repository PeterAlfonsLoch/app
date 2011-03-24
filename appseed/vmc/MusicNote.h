// MusicNote.h: interface for the CMusicNote class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICNOTE_H__19D38179_0B6A_4C52_BCD5_89753E856290__INCLUDED_)
#define AFX_MUSICNOTE_H__19D38179_0B6A_4C52_BCD5_89753E856290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MusicNotePitch.h"
#include "MusicNoteDuration.h"

class CMusicNote : 
	virtual public CMusicNoteDuration, 
	virtual public CMusicNotePitch  
{
public:
	CMusicNote();
	virtual ~CMusicNote();

};

#endif // !defined(AFX_MUSICNOTE_H__19D38179_0B6A_4C52_BCD5_89753E856290__INCLUDED_)
