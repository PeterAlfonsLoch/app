#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D brush : 
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::brush
   {
   public:


      //      Gdiplus::Brush * m_pbrush;


      Microsoft::WRL::ComPtr<ID2D1Brush>                  m_pbrush;
      Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>        m_psolidbrush;
      Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush>    m_plineargradientbrush;


      brush(sp(::axis::application) papp);
      //virtual void construct(COLORREF crColor);                // CreateSolidBrush
      //virtual void construct(int nIndex, COLORREF crColor);    // CreateHatchBrush
      //virtual void construct(::draw2d::bitmap * pbitmap);                // CreatePatternBrush

      virtual ~brush();

      virtual ID2D1Brush * get_os_brush(::draw2d_direct2d::graphics * pgraphics) const;

      //bool CreateSolidBrush(COLORREF crColor);
      //bool CreateHatchBrush(int nIndex, COLORREF crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      //bool CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      //bool CreateSysColorBrush(int nIndex);


      virtual bool destroy();

      virtual void dump(dump_context & dumpcontext) const;
   };


} // namespace draw2d_direct2d



