#pragma once


class CLASS_DECL_BASE window_graphics :
   virtual public object
{
public:


   int32_t        cx;
   int32_t        cy;
   int32_t        scan;


   window_graphics(::aura::application * papp);
   virtual ~window_graphics();

   virtual void on_create_window(oswindow wnd);

   virtual void create_window_graphics(oswindow interaction_impl, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window();


   //virtual void update_window(COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride = -1,bool bTransferBuffer = true);


   //void update_window(oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride = -1,bool bTransferBuffer = true);

   //
   virtual ::draw2d::graphics * on_begin_draw(oswindow wnd, SIZE sz);


};



