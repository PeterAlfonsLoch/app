// MusicNoteDuration.h: interface for the CMusicNoteDuration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICNOTEDURATION_H__FEBE988F_0A17_4520_9C4C_273987B1CA3E__INCLUDED_)
#define AFX_MUSICNOTEDURATION_H__FEBE988F_0A17_4520_9C4C_273987B1CA3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Music.h"

class CDEHeader;

class CMusicNoteDuration : virtual public CMusic  
{
public:
	int IsNull();
	enum EDuration
	{
		Breve = 1,
		SemiBreve = 2,
		WholeNote = 3,
		HalfNote = 4,
		QuarterNote = 5,
		EighthNote = 6,
		SixteenthNote = 7,
		ThirtySecondNote = 8,
		SixtyFourthNote = 9,
		HundredTwentyEighthNote = 10,
		Tuplet = 32,
	};
	

	static CMusicNoteDuration Null;
	int operator >(const CMusicNoteDuration & mnd) const;
	int operator <(const CMusicNoteDuration & mnd) const;
	int operator ==(const CMusicNoteDuration & mnd) const;
	int operator >=(const CMusicNoteDuration & mnd) const;
	int operator <=(const CMusicNoteDuration & mnd) const;
	CMusicNoteDuration & operator =(const CMusicNoteDuration & mnd);
	CMusicNoteDuration & operator -=(const CMusicNoteDuration & mnd);
	CMusicNoteDuration & operator +=(const CMusicNoteDuration & mnd);
	static TICKS GetDuration(EDuration eduration, CDEHeader & deh);
	static TICKS Quantize(
		const TICKS tkDuration,
		const TICKS tkQuantization,
		TICKS * ptkRemainder = NULL);
	void Quantize(
		const CMusicNoteDuration & mndQuantization,
		CMusicNoteDuration & mndRemainder = Null);

	void GetDuration(
		BaseArray<CMusicNoteDuration,
				CMusicNoteDuration> & mnda,
		CDEHeader & deh,
		CMusicNoteDuration & mndQuantization = Null,
		CMusicNoteDuration & mndRemainder = Null);
	void SetDuration(TICKS tk);
	void SetDuration(EDuration eduration, CDEHeader & deh);
	TICKS GetDuration();
	CMusicNoteDuration();
	CMusicNoteDuration(TICKS tk);
	CMusicNoteDuration(CMusicNoteDuration & mnd);
	virtual ~CMusicNoteDuration();

	TICKS m_tkDuration;

	operator TICKS() const;

};

#endif // !defined(AFX_MUSICNOTEDURATION_H__FEBE988F_0A17_4520_9C4C_273987B1CA3E__INCLUDED_)
