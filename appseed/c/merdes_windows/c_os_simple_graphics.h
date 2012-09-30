#pragma once


class CLASS_DECL_c simple_graphics
{
public:


   ID2D1RenderTarget *     m_pdc;
   IDWriteTextFormat *     m_pfont;
   ID2D1Brush *            m_pbrush;


   simple_graphics();
   ~simple_graphics();


};
