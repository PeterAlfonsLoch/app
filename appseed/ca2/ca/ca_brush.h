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

      virtual BOOL CreateSolidBrush(COLORREF crColor);
      virtual BOOL CreateHatchBrush(int nIndex, COLORREF crColor);
      virtual BOOL CreateBrushIndirect(const LOGBRUSH* lpLogBrush);
      virtual BOOL CreatePatternBrush(::ca::bitmap* pBitmap);
#ifdef WINDOWS
      virtual BOOL CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
#endif
      virtual BOOL CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
      virtual BOOL CreateSysColorBrush(int nIndex);

      virtual int GetLogBrush(LOGBRUSH* pLogBrush);

      // Implementation
   public:
#ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
#endif
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
