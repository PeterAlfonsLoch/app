// MSQuantize.h: interface for the CMSQuantize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSQUANTIZE_H__9013F67F_AF05_488E_9B9E_8622BC7C9036__INCLUDED_)
#define AFX_MSQUANTIZE_H__9013F67F_AF05_488E_9B9E_8622BC7C9036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VMS_.h"

class CMSNotes;

class CMSQuantize  
{
public:
//	CMSQuantize();
//	virtual ~CMSQuantize();
    static VMSRESULT Quantize(
        DWORD tkQuarterNote,
        unsigned short ushQuantize,
        DWORD tkMaximum,
        DWORD tkPosition,
        LPDWORD lptkPosition,
        DWORD tkDelta,
        LPDWORD lptkDelta,
        CMSNotes * lpaNotes,
        short shPositionY);

};

#endif // !defined(AFX_MSQUANTIZE_H__9013F67F_AF05_488E_9B9E_8622BC7C9036__INCLUDED_)
