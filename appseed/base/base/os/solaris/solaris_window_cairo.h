

class CLASS_DECL_ca window_cairo :
   public window_graphics
{
public:


   cairo_t *                     m_cairo;
   cairo_surface_t *             m_cairosurface;
   cairo_t *                     m_cairoSource;
   cairo_surface_t *             m_cairosurfaceSource;
   simple_memory                 m_mem;


   window_cairo();
   virtual ~window_cairo();

   virtual void create(oswindow window, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy();

   virtual void update_window(oswindow window, COLORREF * pOsBitmapData, LPCRECT lpcrect, int iStride = -1);

};
