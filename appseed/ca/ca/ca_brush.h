#pragma once

namespace ca
{

   class CLASS_DECL_ca brush :
      virtual public graphics_object
   {
   public:


      COLORREF    m_crColor;


      virtual void construct(COLORREF crColor);                // CreateSolidBrush
      virtual void construct(int nIndex, COLORREF crColor);    // CreateHatchBrush
      virtual void construct(bitmap * pbitmap);                // CreatePatternBrush

      virtual bool CreateStockObject(int nIndex);
      virtual bool CreateSolidBrush(COLORREF crColor);
      virtual bool CreateHatchBrush(int nIndex, COLORREF crColor);
      virtual bool CreateBrushIndirect(const LOGBRUSH* lpLogBrush);
      virtual bool CreatePatternBrush(::ca::bitmap* pBitmap);
#ifdef WINDOWS
      virtual bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
#endif
      virtual bool CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      virtual bool CreateSysColorBrush(int nIndex);

      virtual int GetLogBrush(LOGBRUSH* pLogBrush);

      brush & operator = (const ::ca::brush & brushSrc);

      virtual void dump(dump_context & dumpcontext) const;
   };

   class CLASS_DECL_ca brush_sp :
      virtual public smart_pointer < brush >
   {
   public:


      brush_sp()
      {
      }

      brush_sp(const smart_pointer < brush > & br) :
         smart_pointer < brush > (br)
      {
      }

      brush_sp(::ca::application * papp) :
         smart_pointer < brush > (papp)
      {
      }

      // CreateSolidBrush
      brush_sp(::ca::application * papp, COLORREF crColor) :
         smart_pointer < brush > (papp)
      {
         m_p->construct(crColor);
      }

      // CreateHatchBrush
      brush_sp(::ca::application * papp, int nIndex, COLORREF crColor) :
         smart_pointer < brush > (papp)
      {
         m_p->construct(nIndex, crColor);
      }
      // CreatePatternBrush
      brush_sp(::ca::application * papp, bitmap * pbitmap) :
         smart_pointer < brush > (papp)
      {
         m_p->construct(pbitmap);
      }

      brush_sp & operator = (brush * pbrush)
      {
         m_p = pbrush;
         return *this;
      }
   };


} // namespace ca
