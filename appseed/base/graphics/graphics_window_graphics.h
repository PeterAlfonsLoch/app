#pragma once


class CLASS_DECL_BASE window_graphics :
   virtual public object
{
public:


   int32_t                       m_cx;
   int32_t                       m_cy;
   int32_t                       m_iScan;
   ::user::interaction_impl *    m_pimpl;


   window_graphics(::aura::application * papp);
   virtual ~window_graphics();


   virtual void on_create_window(::user::interaction_impl * pimpl);


   virtual void create_window_graphics(int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();


   virtual void update_window();


   virtual ::draw2d::graphics * on_begin_draw();


};




