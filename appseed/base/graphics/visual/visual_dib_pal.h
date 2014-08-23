#pragma once

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

typedef void * HPALETTE;

#endif

class DibPal
{
public:
   DibPal();

   void create(::draw2d::dib * pdib);


   HPALETTE m_hpalette;

public:
   virtual ~DibPal();
};
