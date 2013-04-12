#pragma once

#if defined(LINUX) || defined(MACOS)

typedef void * HPALETTE;

#endif

class DibPal
{
public:
   DibPal();

   void create(::ca::dib * pdib);


   HPALETTE m_hpalette;

public:
   virtual ~DibPal();
};
