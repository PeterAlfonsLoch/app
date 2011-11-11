#include "StdAfx.h"

LyricEventsV1::LyricEventsV1()
:LyricEventV1()
{
}

LyricEventsV1::~LyricEventsV1()
{

}

imedia::position LyricEventsV1::GetCurrentTkTokenPosition()
{
   if(m_iCurrentToken < 0)
      return 0x7fffffff;
   if(m_iCurrentToken >= m_tkaTokensPosition.get_size())
      return 0x7fffffff;
   return m_tkaTokensPosition.get_at(m_iCurrentToken);
}

void LyricEventsV1::Reset()
{
   m_iCurrentToken = 0;
   m_iCurrentNote = 0;
   m_tkaTokensPosition.remove_all();

}

//LyricEventV1 * LyricEventsV1::GetCurrentEvent()
//{
//   m_Event.m_Union.m_Event.m_nType =  m_nType;
//   m_Event.m_Union.m_Event.m_nType =  m_nType;
//   m_Event.m_Union.m_Event.m_nCurrentIndex =  m_nCurrentIndex;
//   return &m_Event;
//
//}


int LyricEventsV1::GetClassOrder()
{
   return 1;
}

int LyricEventsV1::GetPositionToken(imedia::position tkPosition)
{
    int i = 0;
    while(i < m_tkaTokensPosition.get_size())
    {
        if(tkPosition < m_tkaTokensPosition.get_at(i))
            break;
        i++;
    }
    return i - 1;
}
