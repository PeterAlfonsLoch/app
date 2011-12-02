#pragma once


class CLASS_DECL_ca clock :
   public clock_interface
{
protected:


   point    m_point;
   size     m_size;


public:


   ::ax::font    m_font;
   ::ax::font    m_fontHour;
   ::ax::font    m_fontMinute;
   ::ax::font    m_fontSpin;


   clock(::ax::application * papp);

   void GetRect(LPRECT lprect, enum EElement eelement);

   void _001OnDraw(::ax::graphics * pdc);

   void set_pos(point pt, size sz);



};