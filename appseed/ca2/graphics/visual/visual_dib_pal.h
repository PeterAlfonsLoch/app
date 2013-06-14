#pragma once

#if defined(LINUX) || defined(MACOS)

typedef void * HPALETTE;

#endif

class DibPal
{
public:
   DibPal();

   void create(::ca2::dib * pdib);


   HPALETTE m_hpalette;

public:
   virtual ~DibPal();
};
