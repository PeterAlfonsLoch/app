#pragma once


namespace draw2d_gl2d
{


   class CLASS_DECL_DRAW2D_GL2D brush : 
      virtual public ::draw2d::brush
   {
   public:


      //plusplus::Brush * m_pbrush;


      brush(::aura::application * papp);
      //virtual void construct(COLORREF crColor);                // create_solid
      //virtual void construct(int32_t nIndex, COLORREF crColor);    // CreateHatchBrush
      //virtual void construct(::draw2d::bitmap * pbitmap);                // CreatePatternBrush
      virtual ~brush();


      //virtual void * get_os_data() const;



      //bool create_solid(COLORREF crColor);
      //bool CreateHatchBrush(int32_t nIndex, COLORREF crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
      //bool CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      //bool CreateSysColorBrush(int32_t nIndex);


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_gl2d


