#pragma once


namespace ca
{


   class CLASS_DECL_ca pen :
      virtual public ::ca::graphics_object
   {
   public:


      enum e_type
      {
         type_null,
         type_solid,
      };



      e_type      m_etype;
      double      m_dWidth;
      COLORREF    m_cr;


      virtual bool create_null();
      virtual bool create_solid(double dWidth, COLORREF crColor);


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

      pen_sp(::ca::application * papp, int nWidth, COLORREF crColor) :
         smart_pointer < pen > (papp)
      {
         m_p->create_solid(nWidth, crColor);
      }

/*
      pen_sp(::ca::application * papp, int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
         int nStyleCount = 0, const DWORD* lpStyle = NULL) :
         smart_pointer < pen > (papp)
      {
         m_p->construct(nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle);
      }
*/

      pen_sp & operator = (pen * ppen)
      {
         m_p = ppen;
         return *this;
      }

   };


} // namespace ca
