#pragma once


class CDEHeader
{
public:
   CDEHeader();
   virtual ~CDEHeader();
void SetTicks(TICKS tk);
TICKS GetTicks();

TICKS m_tk;
};