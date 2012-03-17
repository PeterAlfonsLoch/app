#pragma once


namespace ca
{


   class CLASS_DECL_ca pen : 
      virtual public ::ca::graphics_object
   {
   public:


      int         m_nPenStyle;
      double      m_dPenWidth;
      COLORREF    m_crPenColor;


      virtual void construct(int nPenStyle, double dWidth, COLORREF crColor);
      virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL);
      virtual BOOL CreatePen(int nPenStyle, double dWidth, COLORREF crColor);
      virtual BOOL CreatePen(int nPenStyle, double nWidth, const LOGBRUSH * pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL);


      pen & operator = (const pen & penSrc);


      virtual void dump(dump_context & dumpcontext) const;

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