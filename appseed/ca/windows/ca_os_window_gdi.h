

class CLASS_DECL_ca window_gdi :
   public window_graphics
{
public:


   HBITMAP              m_hbitmap;
   HBITMAP              m_hbitmapOld;
   BITMAPINFO           m_bitmapinfo;
   COLORREF *           m_pcolorref;
   HDC                  m_hdc;


   window_gdi();
   virtual ~window_gdi();

   virtual void create(oswindow window, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy();

   virtual void update_window(oswindow window, COLORREF * pcolorref, LPCRECT lpcrect, int iStride = -1);

};
