#pragma once


class CLASS_DECL_ca2 clock :
   public clock_interface
{
protected:


   point    m_point;
   size     m_size;


public:


   ::ca2::font    m_font;
   ::ca2::font    m_fontHour;
   ::ca2::font    m_fontMinute;
   ::ca2::font    m_fontSpin;


   clock(sp(::ca2::application) papp);

   void GetRect(LPRECT lprect, enum EElement eelement);

   void _001OnDraw(::ca2::graphics * pdc);

   void set_pos(point pt, size sz);



};