#pragma once



class CLASS_DECL_ca window_graphics
{
public:


   int32_t        cx;
   int32_t        cy;

   
   window_graphics();
   virtual ~window_graphics();


   virtual void create(int64_t cx, int64_t cy);
   virtual void destroy();


   virtual void update_window(oswindow window, COLORREF * pcolorref, LPCRECT lpcrect);


   static void update_window(window_graphics * & pdata, oswindow window, COLORREF * pcolorref, LPCRECT lpcrect);



};