// MusicNoteDuration.cpp: implementation of the CMusicNoteDuration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MusicNoteDuration.h"
#include "DEHeader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMusicNoteDuration CMusicNoteDuration::Null(0xFFFFFFFF);

CMusicNoteDuration::CMusicNoteDuration()
{
	SetDuration(0);
}

CMusicNoteDuration::CMusicNoteDuration(TICKS tk)
{
	SetDuration(tk);
}

CMusicNoteDuration::CMusicNoteDuration(
	CMusicNoteDuration & mnd)
{
	operator=(mnd);
}

CMusicNoteDuration::~CMusicNoteDuration()
{

}

TICKS CMusicNoteDuration::GetDuration()
{
	return m_tkDuration;
}

void CMusicNoteDuration::SetDuration(TICKS tk)
{
	m_tkDuration = tk;
}
void  CMusicNoteDuration::SetDuration(EDuration eduration, CDEHeader & pdeh)
{
	m_tkDuration = GetDuration(eduration, pdeh);
}
void CMusicNoteDuration::GetDuration(
	BaseArray<CMusicNoteDuration,
		CMusicNoteDuration> & mnda,
	CDEHeader & deh,
	CMusicNoteDuration & mndQuantization,
	CMusicNoteDuration & mndRemainder)
{

	CMusicNoteDuration mnd(*this);
	CMusicNoteDuration mndElement;

	if(!mndQuantization.IsNull())
	{
		mnd.Quantize(
			mndQuantization,
			mndRemainder);
	}

	mndElement.SetDuration(Breve, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	mndElement.SetDuration(SemiBreve, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	mndElement.SetDuration(WholeNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	mndElement.SetDuration(HalfNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	mndElement.SetDuration(QuarterNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}
	mndElement.SetDuration(EighthNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	mndElement.SetDuration(SixteenthNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	mndElement.SetDuration(ThirtySecondNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	mndElement.SetDuration(SixtyFourthNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}
	
	mndElement.SetDuration(HundredTwentyEighthNote, deh);
	while(mnd > mndElement)
	{
		mnd -= mndElement;
		mnda.Add(mndElement);
	}

	if(!mndRemainder.IsNull())
	{
		mnd += mnd;
	}

}

TICKS CMusicNoteDuration::GetDuration(EDuration eduration, CDEHeader & deh)
{
	switch(eduration)
	{
	case Breve:
		return deh.GetTicks() * 16;
	case SemiBreve:
		return deh.GetTicks() * 8;
	case WholeNote:
		return deh.GetTicks() * 4;
	case HalfNote:
		return deh.GetTicks() * 2;
	case QuarterNote:
		return deh.GetTicks();
	case EighthNote:
		return deh.GetTicks() / 2;
	case SixteenthNote:
		return deh.GetTicks() / 4;
	case ThirtySecondNote:
		return deh.GetTicks() / 16;
	case SixtyFourthNote:
		return deh.GetTicks() / 32;
   default:
      ASSERT(FALSE);
      return deh.GetTicks();
	}
}

TICKS CMusicNoteDuration::Quantize(
	TICKS tkDuration,
	TICKS tkQuantization,
	TICKS * ptkRemainder)
{
	ASSERT(tkQuantization != 0);
	TICKS tkNote = (tkDuration / tkQuantization) * tkQuantization;
	if(ptkRemainder != NULL)
	{
		*ptkRemainder = tkDuration - tkNote;
	}
	return tkNote;
}

int CMusicNoteDuration::operator >(const CMusicNoteDuration & mnd) const
{
	return m_tkDuration > mnd.m_tkDuration;
}
int CMusicNoteDuration::operator <(const CMusicNoteDuration & mnd) const
{
	return m_tkDuration < mnd.m_tkDuration;
}
int CMusicNoteDuration::operator ==(const CMusicNoteDuration & mnd) const
{
	return m_tkDuration == mnd.m_tkDuration;
}

int CMusicNoteDuration::operator >=(const CMusicNoteDuration & mnd) const
{
	return m_tkDuration >= mnd.m_tkDuration;
}
int CMusicNoteDuration::operator <=(const CMusicNoteDuration & mnd) const
{
	return m_tkDuration <= mnd.m_tkDuration;
}

CMusicNoteDuration & CMusicNoteDuration::operator =(const CMusicNoteDuration & mnd)
{
	m_tkDuration = mnd.m_tkDuration;
	return *this;
}
CMusicNoteDuration & CMusicNoteDuration::operator -=(const CMusicNoteDuration & mnd)
{
	m_tkDuration = m_tkDuration - mnd.m_tkDuration;
	return *this;
}
CMusicNoteDuration & CMusicNoteDuration::operator +=(const CMusicNoteDuration & mnd)
{
	m_tkDuration = m_tkDuration - mnd.m_tkDuration;
	return *this;
}


void CMusicNoteDuration::Quantize(
	const CMusicNoteDuration & mndQuantization,
	CMusicNoteDuration & mndRemainder)
{
	TICKS tk;
	SetDuration(Quantize(GetDuration(),mndQuantization, &tk));
	mndRemainder = tk;
}

int CMusicNoteDuration::IsNull()
{
	return m_tkDuration == Null.m_tkDuration;

}

CMusicNoteDuration::operator TICKS() const
{
	return m_tkDuration;
}
