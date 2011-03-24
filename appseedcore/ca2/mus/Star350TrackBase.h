// Star350TrackBase.h: interface for the Star350TrackBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAR350TRACKBASE_H__89B8E117_5F81_49EF_A197_2F5DF546CAE1__INCLUDED_)
#define AFX_STAR350TRACKBASE_H__89B8E117_5F81_49EF_A197_2F5DF546CAE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

   class Star350EventBase;

class CLASS_DECL_ca Star350TrackBase  : public ::radix::object
{
    ;
public:
   
   Star350TrackBase();
   virtual ~Star350TrackBase();

public:
   virtual VMSRESULT GetNextEventPosition(imedia::position *tkPosition, imedia::position tkMax) = 0;
   virtual int GetFlags() = 0;
   virtual VMSRESULT GetEvent(
      MidiEventBase * pEvent,
      imedia::position   tkMax,
      BOOL   bTkMaxInclusive) = 0;
   virtual imedia::position GetPosition() = 0;
   virtual VMSRESULT seek_begin() = 0;
};

#endif // !defined(AFX_STAR350TRACKBASE_H__89B8E117_5F81_49EF_A197_2F5DF546CAE1__INCLUDED_)
