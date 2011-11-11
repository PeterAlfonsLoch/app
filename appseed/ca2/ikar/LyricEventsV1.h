#pragma once

// This class keep track of
// lyrics events positions.

class CLASS_DECL_ca LyricEventsV1 : public LyricEventV1 
{
public:
   
   
   imedia::position_array            m_tkaTokensPosition; // in ticks


   LyricEventsV1();
   virtual ~LyricEventsV1();

   int GetPositionToken(imedia::position tkPosition);
   virtual int GetClassOrder();
   static const int type;
   void Reset();
   imedia::position GetCurrentTkTokenPosition();

};
