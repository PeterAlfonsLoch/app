#pragma once

class DibPal
{
public:
   DibPal(void);

   void create(::ca::dib * pdib);

   HPALETTE m_hpalette;

public:
   virtual ~DibPal(void);
};
