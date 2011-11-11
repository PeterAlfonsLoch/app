#pragma once

namespace ca
{

   /////////////////////////////////////////////////////////////////////////////
   // ::ca::graphics_object subclasses (drawing tools)

   class CLASS_DECL_ca pen : 
      virtual public ::ca::graphics_object
   {
   public:

      virtual void construct(int nPenStyle, int nWidth, COLORREF crColor);
      virtual void construct(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
         int nStyleCount = 0, const DWORD* lpStyle = NULL);
      virtual BOOL CreatePen(int nPenStyle, int nWidth, COLORREF crColor);
      virtual BOOL CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
         int nStyleCount = 0, const DWORD* lpStyle = NULL);
      virtual BOOL CreatePenIndirect(LPLOGPEN lpLogPen);

   // Attributes
      virtual int GetLogPen(LOGPEN* pLogPen);
      virtual int GetExtLogPen(EXTLOGPEN* pLogPen);

   // Implementation
   public:
   #ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

   class CLASS_DECL_ca pen_sp :
      virtual public smart_pointer < pen >
   {
   public:

      pen_sp()
      {
      }

      pen_sp(const smart_pointer < pen > & p) :
         smart_pointer < pen > (p)
      {
      }

      pen_sp(::ca::application * papp) : 
         smart_pointer < pen > (papp)
      {
      }

      pen_sp(::ca::application * papp, int nPenStyle, int nWidth, COLORREF crColor) :
         smart_pointer < pen > (papp)
      {
         m_p->construct(nPenStyle, nWidth, crColor); 
      }

      pen_sp(::ca::application * papp, int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
         int nStyleCount = 0, const DWORD* lpStyle = NULL) :
         smart_pointer < pen > (papp)
      {
         m_p->construct(nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle); 
      }

      pen_sp & operator = (pen * ppen)
      {
         m_p = ppen;
         return *this;
      }
   };


} // namespace ca