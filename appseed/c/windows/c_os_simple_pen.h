#pragma once


class CLASS_DECL_c simple_pen
{
public:

   
   HPEN                  m_hpen;


   simple_pen();
   ~simple_pen();

   bool create_solid(int iWidth, COLORREF cr);

   bool destroy();



};

