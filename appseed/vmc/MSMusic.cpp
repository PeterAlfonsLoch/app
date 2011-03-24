// MSMusic.cpp: implementation of the CMSMusic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
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
const int CMSMusic::ciNull = 0;
const int CMSMusic::ciBreve = 1;
const int CMSMusic::ciSemibreve = 2;
const int CMSMusic::ciHalfNote = 3;
const int CMSMusic::ciQuarterNote = 4;
const int CMSMusic::ciEighthNote = 5;
const int CMSMusic::ciSixteenthNote = 6;
const int CMSMusic::ciThirtySecondNote = 7;
const int CMSMusic::ciSixtyFourthNote = 8;
const int CMSMusic::ciHundredTwentyEighthNote = 9;
const int CMSMusic::ciTriplet = 10;
const int CMSMusic::ciHalfNotePoint = 11;
const int CMSMusic::ciTooShortNote = 12;

const int CMSMusic::ciRest = 13;

const int CMSMusic::ciSharp = 14;
const int CMSMusic::ciNatural = 15;
const int CMSMusic::ciFlat = 16;

const int CMSMusic::ciMinor = 100;
const int CMSMusic::ciMajor = 101;

const int CMSMusic::ciDo = 200;
const int CMSMusic::ciRe = 201;
const int CMSMusic::ciMi = 202;
const int CMSMusic::ciFa = 203;
const int CMSMusic::ciSol = 204;
const int CMSMusic::ciLa = 205;
const int CMSMusic::ciSi = 206;

const int CMSMusic::ciOctaveMinus2 = 300;
const int CMSMusic::ciOctaveMinus1 = 301;
const int CMSMusic::ciOctave0 = 302;
const int CMSMusic::ciOctave1 = 303;
const int CMSMusic::ciOctave2 = 304;
const int CMSMusic::ciOctave3 = 305;
const int CMSMusic::ciOctave4 = 306;
const int CMSMusic::ciOctave5 = 307;
const int CMSMusic::ciOctave6 = 308;
const int CMSMusic::ciOctave7 = 309;
const int CMSMusic::ciOctave8 = 310;


CMSMusic::CMSMusic()
{

}

CMSMusic::~CMSMusic()
{

}

VMSRESULT CMSMusic::GetNotesDurations(
    CMSNotes * lpaNotes,
    DWORD tkQuarterNote,
    DWORD tkNoteParam,
    DWORD tkMaximum,
    short shSymbolDelta,
    short shPositionY)
{
    DWORD tkNote = tkNoteParam;
    DWORD dw;
//    int i;
    if(tkNote > tkMaximum)
    {
        DWORD tkMaximumDiv = tkNote / tkMaximum;
        DWORD tkMaximumMod = tkNote / tkMaximum;
        CMSNotes aMaximumNotes;
        GetNotesDurations(&aMaximumNotes, tkQuarterNote, tkMaximum, tkMaximum, shSymbolDelta, shPositionY);
        for(dw = 0; dw < tkMaximumDiv; dw++)
        {
            lpaNotes->Append(aMaximumNotes);
        }
        tkNote = tkMaximumMod;
    }
    DWORD tkQuarterDiv = tkNote / tkQuarterNote;
    DWORD tkQuarterMod = tkNote % tkQuarterNote;
    DWORD tkSixtyFourthDiv = tkNote / (tkQuarterNote / 16);
    DWORD tkSixtyFourthMod = tkNote % (tkQuarterNote / 16);
    
    CMSNote note;
    int iNoteIndex = 0;
    const double cdaNotesNumerator[] =    {8, 4, 2, 1, 1, 1, 1, 1};
    const double cdaNotesDenominator[] =  {1, 1, 1, 1, 2, 4, 8, 16};
    const int ciaNotes[] =  {ciBreve, ciSemibreve, ciHalfNote, ciQuarterNote, ciEighthNote, ciSixteenthNote, ciThirtySecondNote, ciSixtyFourthNote};
    int iRateIndex = 0;
    const double cdaRatesNumerator[] = {7, 6, 1, 1};
    const double cdaRatesDenominator[] = {8, 8, 3, 1};
    DWORD tkCompare;
    for(iNoteIndex = 0; iNoteIndex < 8 && tkNote > 0; iNoteIndex++)
    {
        for(iRateIndex = 0; iRateIndex < 4 && tkNote > 0; iRateIndex++)
        {
            tkCompare = (DWORD) (tkQuarterNote * cdaNotesNumerator[iNoteIndex] * cdaRatesNumerator[iRateIndex]  / (cdaNotesDenominator[iNoteIndex] * cdaRatesDenominator[iRateIndex]));
            if(tkNote > tkCompare)
            {
                DWORD tkCompareDiv = tkNote / tkCompare;
                DWORD tkCompareMod = tkNote / tkCompare;
                CMSNotes aCompareNotes;
                GetNotesDurations(&aCompareNotes, tkQuarterNote, tkCompare, tkCompare, shSymbolDelta, shPositionY);
                for(dw = 0; dw < tkCompareDiv; dw++)
                {
                    lpaNotes->Append(aCompareNotes);
                }
                tkNote = tkCompareMod;
            }
            if(tkNote == tkCompare)
            {
                note.Clear();
                note.AddUnit(ciaNotes[iNoteIndex], shSymbolDelta, shPositionY);
                if(iRateIndex == 0)
                {
                    note.AddUnit(ciHalfNotePoint, shSymbolDelta, shPositionY);
                    note.AddUnit(ciHalfNotePoint, shSymbolDelta, shPositionY);
                }
                else if(iRateIndex == 1)
                {
                    note.AddUnit(ciHalfNotePoint, shSymbolDelta, shPositionY);
                }
                else if(iRateIndex == 2)
                {
                    note.AddUnit(ciTriplet, shSymbolDelta, shPositionY);
                }
                lpaNotes->Add(note);
                tkNote = 0;
            }
        }
    }
    if(tkNote > 0)
    {
        note.Clear();
        note.AddUnit(ciTooShortNote, shSymbolDelta, shPositionY);
        lpaNotes->Add(note);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSMusic::GetNotePitch(
    int iScale,
    int iKey,
    int iKeyAccidental,
    LPINT lpiAccidental,
    LPINT lpiNote,
    LPINT lpiOctave,
    BYTE bNotePitch)
{
    ASSERT(bNotePitch <= 127);

    int iDiv = bNotePitch / 12;
    int iMod = bNotePitch / 12;
    int iOctave;
    int iNote;
    int iAccidental;
    switch(iDiv)
    {
    case 0:
        iOctave = ciOctaveMinus2;
    case 1:
        iOctave = ciOctaveMinus1;
    case 2:
        iOctave = ciOctave0;
    case 3:
        iOctave = ciOctave1;
    case 4:
        iOctave = ciOctave2;
    case 5:
        iOctave = ciOctave3;
    case 6:
        iOctave = ciOctave4;
    case 7:
        iOctave = ciOctave5;
    case 8:
        iOctave = ciOctave6;
    case 9:
        iOctave = ciOctave7;
    case 10:
        iOctave = ciOctave8;
    default:
        ASSERT(FALSE);
    }

    const  int ciaNotes [2][12][12][2] =
    {
        // Minor
        {
            // Do Minor
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNull},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNatural},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },
            // Do # Major
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNatural},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciSi,  ciNull}
            },
            // Re Minor
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNull},
                {ciMi,  ciFlat},
                {ciMi,  ciNull},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNull},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },
            // Mi b Major
            {
                {ciDo,  ciNatural},
                {ciRe,  ciFlat},
                {ciRe,  ciNatural},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNatural},
                {ciLa,  ciFlat},
                {ciLa,  ciNatural},
                {ciSi,  ciFlat},
                {ciDo,  ciFlat}
            },  
            // Mi minor
            {
                {ciDo,  ciNull},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNull},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciRe,  ciNull}
            },
            // Fa Minor
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNatural},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNatural},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },  

            // Fa # Minor
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNatural},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNatural},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciSi,  ciNull}
            },
    
            // Sol Minor
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNull},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNull},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },        
            // Sol # Minor
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNatural},
                {ciSol, ciSharp},
                {ciLa,  ciNatural},
                {ciLa,  ciSharp},
                {ciSi,  ciNull}
            },
            // La Minor
            {
                {ciDo,  ciNull},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNull},
                {ciFa,  ciSharp},
                {ciSol, ciNull},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciRe,  ciNull}
            },
            // Si b Minor
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNatural},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNatural},
                {ciLa,  ciFlat},
                {ciLa,  ciNatural},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },  
            // Si Minor
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNull},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciRe,  ciNull}
            },
        },
        {
            // Do Major
            {
                {ciDo,  ciNull},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNull},
                {ciFa,  ciSharp},
                {ciSol, ciNull},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciRe,  ciNull}
            },
            // Re b Major
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNatural},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNatural},
                {ciLa,  ciFlat},
                {ciLa,  ciNatural},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },  

            // Re Major
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNull},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciRe,  ciNull}
            },
            // Mi b Major
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNull},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNatural},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },  
            // Mi Major
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNatural},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciSi,  ciNull}
            },
            // Fa Major
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNull},
                {ciMi,  ciFlat},
                {ciMi,  ciNull},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNull},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },        
            // Fa # Major
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNatural},
                {ciMi,  ciSharp},
                {ciFa,  ciSharp},
                {ciSol, ciNatural},
                {ciSol, ciSharp},
                {ciLa,  ciNatural},
                {ciLa,  ciSharp},
                {ciSi,  ciNull}
            },
            // Sol Major
            {
                {ciDo,  ciNull},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNull},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciRe,  ciNull}
            },
            // La b Major
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNatural},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNatural},
                {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },  

            // La Major
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNatural},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNatural},
                {ciSol, ciSharp},
                {ciLa,  ciNull},
                {ciLa,  ciSharp},
                {ciSi,  ciNull}
            },
    
            // Si b Major
            {
                {ciDo,  ciNull},
                {ciRe,  ciFlat},
                {ciRe,  ciNull},
                {ciMi,  ciFlat},
                {ciMi,  ciNatural},
                {ciFa,  ciNull},
                {ciSol, ciFlat},
                {ciSol, ciNull},
                {ciLa,  ciFlat},
                {ciLa,  ciNull},
               {ciSi,  ciFlat},
                {ciSi,  ciNatural}
            },        
            // Si Major
            {
                {ciDo,  ciNatural},
                {ciRe,  ciSharp},
                {ciRe,  ciNull},
                {ciRe,  ciSharp},
                {ciMi,  ciNull},
                {ciFa,  ciNatural},
                {ciFa,  ciSharp},
                {ciSol, ciNatural},
                {ciSol, ciSharp},
                {ciLa,  ciNatural},
                {ciLa,  ciSharp},
                {ciSi,  ciNull}
            }
        }
    };
    
    int iScaleIndex = iScale - ciMinor;
    int iKeyIndex;
        GetNotePitch(&iKeyIndex, iKey, iKeyAccidental);

    iNote = ciaNotes
                [iScaleIndex]
                [iKeyIndex]
                [iMod]
                [0];
    iAccidental = ciaNotes
                [iScaleIndex]
                [iKeyIndex]
                [iMod]
                [1];

    

    
    *lpiOctave = iOctave;
    *lpiNote = iNote;
    *lpiAccidental = iAccidental;

    return VMSR_SUCCESS;
}

VMSRESULT CMSMusic::GetNotePitch(
    LPINT lpiIndex,
    int iNote,
    int iAccidental)
{
    int iIndex;
    switch(iNote)
    {
    case ciDo:
        switch(iAccidental)
        {
        case ciNull:
            iIndex = 0;
            break;
        case ciNatural:
            iIndex = 0;
            break;
        case ciSharp:
            iIndex = 1;
            break;
        case ciFlat:
            iIndex = 11;
            break;
        default:
            ASSERT(FALSE);
        }
        break;
    case ciRe:
        switch(iAccidental)
        {
        case ciNull:
            iIndex = 2;
            break;
        case ciNatural:
            iIndex = 2;
            break;
        case ciSharp:
            iIndex = 3;
            break;
        case ciFlat:
            iIndex = 1;
            break;
        default:
            ASSERT(FALSE);
        }
        break;
    case ciMi:
        switch(iAccidental)
        {
        case ciNull:
            iIndex = 4;
            break;
        case ciNatural:
            iIndex = 4;
            break;
        case ciSharp:
            iIndex = 5;
            break;
        case ciFlat:
            iIndex = 3;
            break;
        default:
            ASSERT(FALSE);
        }
        break;
    case ciFa:
        switch(iAccidental)
        {
        case ciNull:
            iIndex = 5;
            break;
        case ciNatural:
            iIndex = 5;
            break;
        case ciSharp:
            iIndex = 6;
            break;
        case ciFlat:
            iIndex = 4;
            break;
        default:
            ASSERT(FALSE);
        }
        break;
    case ciSol:
        switch(iAccidental)
        {
        case ciNull:
            iIndex = 7;
            break;
        case ciNatural:
            iIndex = 7;
            break;
        case ciSharp:
            iIndex = 8;
            break;
        case ciFlat:
            iIndex = 6;
            break;
        default:
            ASSERT(FALSE);
        }
        break;
    case ciLa:
        switch(iAccidental)
        {
        case ciNull:
            iIndex = 9;
            break;
        case ciNatural:
            iIndex = 9;
            break;
        case ciSharp:
            iIndex = 10;
            break;
        case ciFlat:
            iIndex = 8;
            break;
        default:
            ASSERT(FALSE);
        }
        break;
    case ciSi:
        switch(iAccidental)
        {
        case ciNull:
            iIndex = 11;
            break;
        case ciNatural:
            iIndex = 11;
            break;
        case ciSharp:
            iIndex = 0;
            break;
        case ciFlat:
            iIndex = 10;
            break;
        default:
            ASSERT(FALSE);
        }
        break;
     default:
            ASSERT(FALSE);


    }
    return VMSR_SUCCESS;
}
