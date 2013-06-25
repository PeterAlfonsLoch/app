#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 brush :
      virtual public graphics_object
   {
   public:


      enum e_type
      {

         type_null,
         type_solid,
         type_linear_gradient_point_color,

      };


      COLORREF    m_cr;
      e_type      m_etype;
      point       m_pt1;
      point       m_pt2;
      COLORREF    m_cr1;
      COLORREF    m_cr2;


      brush();


      //virtual void construct(COLORREF crColor);                // create_solid
      //virtual void construct(int32_t nIndex, COLORREF crColor);    // CreateHatchBrush
      //virtual void construct(bitmap * pbitmap);                // CreatePatternBrush

      virtual bool create_null();
      virtual bool create_solid(COLORREF crColor);
      virtual bool CreateHatchBrush(int32_t nIndex, COLORREF crColor);
      virtual bool CreateBrushIndirect(const LOGBRUSH* lpLogBrush);
      virtual bool CreatePatternBrush(::ca2::bitmap* pBitmap);
#ifdef WINDOWS
      virtual bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
#endif
      virtual bool CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      virtual bool CreateSysColorBrush(int32_t nIndex);

      virtual bool CreateLinearGradientBrush(point p1, point p2, COLORREF cr1, COLORREF cr2);

      virtual int32_t GetLogBrush(LOGBRUSH* pLogBrush);

      brush & operator = (const ::ca2::brush & brushSrc);

      virtual void dump(dump_context & dumpcontext) const;
   };

   class CLASS_DECL_ca2 brush_sp :
      virtual public ::ca::smart_pointer < brush >
   {
   public:


      brush_sp()
      {
      }

      brush_sp(const ::ca::smart_pointer < brush > & br) :
         ::ca::smart_pointer < brush > (br)
      {
      }

      brush_sp(allocatorsp allocer) :
         ::ca::smart_pointer < brush > (allocer)
      {
      }

      // create_solid
      brush_sp(allocatorsp allocer, COLORREF crColor) :
         ::ca::smart_pointer < brush > (allocer)
      {
         m_p->create_solid(crColor);
      }

/*
      // CreateHatchBrush
      brush_sp(sp(::ca2::application) papp, int32_t nIndex, COLORREF crColor) :
         ::ca::smart_pointer < brush > (papp)
      {
         m_p->construct(nIndex, crColor);
      }
      // CreatePatternBrush
      brush_sp(sp(::ca2::application) papp, bitmap * pbitmap) :
         ::ca::smart_pointer < brush > (papp)
      {
         m_p->construct(pbitmap);
      }
*/

      
      brush_sp & operator = (::ca2::brush * pbrush)
      {

         ::ca::smart_pointer < brush >::operator = (pbrush);
         
         return *this;
         
      }
      
      
   };


} // namespace ca2



