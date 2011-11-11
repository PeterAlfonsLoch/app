#pragma once


class CLASS_DECL_ca LyricEventV1 : public ::radix::object
{
public:
   LyricEventV1(LyricEventV1 & src);
   LyricEventV1();
   virtual ~LyricEventV1();

public:
   virtual int GetClassOrder();

   virtual LyricEventV1 & operator=(const LyricEventV1 & src);
protected:
   int                     m_iID;
public:
   int                     m_iClassOrder;
   int                     m_iType;
   int                     m_iOrder;
   int                     m_iTrack;
   int                     m_iCurrentToken;
   int                     m_iCurrentNote;
   int                     m_iCurrentLine;
   imedia::position         m_tkDelta;
   imedia::position        m_tkPosition;
   ::ca::graphics *                   m_pdc;


   void ToData_(LPDWORD lpdwData, DWORD cbLeft);
   void FromData_(LPDWORD lpdwData);
};