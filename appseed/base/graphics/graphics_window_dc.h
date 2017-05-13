#pragma once


class CLASS_DECL_BASE window_dc :
   virtual public window_graphics
{
public:


   ::draw2d::graphics_sp         m_spgraphics;


   window_dc(::aura::application * papp);
   virtual ~window_dc();


   virtual void update_window();


   ::draw2d::graphics * on_begin_draw();


};
