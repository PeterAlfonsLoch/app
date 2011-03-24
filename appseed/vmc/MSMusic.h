#pragma once

#include "VMS_.h"

class CMSNotes;

class CMSMusic  
{
public:
	CMSMusic();
	virtual ~CMSMusic();

public:
    static VMSRESULT GetNotesDurations(
        CMSNotes * lpaNotes,
        DWORD tkQuarterNote,
        DWORD tkNote,
        DWORD tkMaximum,
        short shSymbolDelta,
        short shPositionY);
    static VMSRESULT GetNotePitch(
        int iScale,
        int iKey,
        int iKeyAccidental,
        LPINT lpiAccidental,
        LPINT lpiNote,
        LPINT lpiOctave,
        BYTE bNotePitch);
    static VMSRESULT GetNotePitch(
        LPINT lpiIndex,
        int iNote,
        int iAccidental);


    static const int ciNull;
    static const int ciBreve;
    static const int ciSemibreve;
    static const int ciHalfNote;
    static const int ciQuarterNote;
    static const int ciEighthNote;
    static const int ciSixteenthNote;
    static const int ciThirtySecondNote;
    static const int ciSixtyFourthNote;
    static const int ciHundredTwentyEighthNote;
    static const int ciTriplet;
    static const int ciHalfNotePoint;
    static const int ciTooShortNote;

    static const int ciRest;
    
    static const int ciSharp;
    static const int ciNatural;
    static const int ciFlat;

    static const int ciMinor;
    static const int ciMajor;

    static const int ciDo;
    static const int ciRe;
    static const int ciMi;
    static const int ciFa;
    static const int ciSol;
    static const int ciLa;
    static const int ciSi;

    static const int ciOctaveMinus2;
    static const int ciOctaveMinus1;
    static const int ciOctave0;
    static const int ciOctave1;
    static const int ciOctave2;
    static const int ciOctave3;
    static const int ciOctave4;
    static const int ciOctave5;
    static const int ciOctave6;
    static const int ciOctave7;
    static const int ciOctave8;




//    static const double daNotesRates[];
//    static const int iaNotes1[];
//    static const int iaNotes2[];
//    static const int iaNotes3[];
//    static const int iaNotes4[];

};
