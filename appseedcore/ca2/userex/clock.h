#pragma once


class CLASS_DECL_ca clock :
   public clock_interface
{
protected:


   point    m_point;
   size     m_size;


public:


   ::ca::font    m_font;
   ::ca::font    m_fontHour;
   ::ca::font    m_fontMinute;
   ::ca::font    m_fontSpin;


   clock(::ca::application * papp);

   void GetRect(LPRECT lprect, enum EElement eelement);

   void _001OnDraw(::ca::graphics * pdc);

   void set_pos(point pt, size sz);



};