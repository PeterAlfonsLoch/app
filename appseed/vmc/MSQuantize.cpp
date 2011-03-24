// MSQuantize.cpp: implementation of the CMSQuantize class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSQuantize.h"

#include "MSMusic.h"
#include "MSNotes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//CMSQuantize::CMSQuantize()
//{

//}

//CMSQuantize::~CMSQuantize()
//{

//}
VMSRESULT CMSQuantize::Quantize(
    DWORD tkQuarterNote,
    unsigned short ushQuantization,
    DWORD tkMaximum,
    DWORD tkPositionParam,
    LPDWORD lptkPosition,
    DWORD tkDelta,
    LPDWORD lptkDelta,
    CMSNotes * lpaNotes, short
    shPositionY)
{
    DWORD tkMod;
    DWORD tkDiv;
    DWORD tkPosition = tkPositionParam;

    tkMod = tkPosition % ushQuantization;
    tkDiv = tkPosition / ushQuantization;
    if(tkMod > ushQuantization / 2u)
        tkPosition = (tkDiv + 1) * ushQuantization;
    else
        tkPosition = tkDiv * ushQuantization;

    *lptkPosition = tkPosition;

    tkDiv = tkDelta / ushQuantization;
    tkMod = tkDelta % ushQuantization;
    if(tkDiv == 0)
        tkDelta = ushQuantization;
    else if(tkMod > ushQuantization / 2u)
        tkDelta = (tkDiv + 1) * ushQuantization;
    else
        tkDelta = tkDiv * ushQuantization;

    *lptkDelta = tkDelta;

    CMSMusic::GetNotesDurations(lpaNotes, tkQuarterNote, tkDelta, tkMaximum, (short)(tkPosition - tkPositionParam), shPositionY);

    return VMSR_SUCCESS;

}
