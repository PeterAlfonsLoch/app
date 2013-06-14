#pragma once


namespace ca2
{


   class graphics;


   class CLASS_DECL_ca2 pen :
      virtual public ::ca2::graphics_object
   {
   public:


      enum e_type
      {
         type_null,
         type_solid,
      };

      enum e_end_cap
      {
         end_cap_flat,
         end_cap_round,
      };


      enum e_line_join
      {
         line_join_miter,
         line_join_bevel,
         line_join_round,
         line_join_miter_clipped,
      };

      e_type            m_etype;
      e_end_cap         m_eendcap;
      e_line_join       m_elinejoin;
      double            m_dWidth;
      COLORREF          m_cr;


      pen();
      virtual ~pen();


      virtual bool create_null();
      virtual bool create_solid(::ca2::graphics * pgraphics, double dWidth, COLORREF crColor);

      virtual e_end_cap get_end_cap();
      virtual bool set_end_cap(e_end_cap eendcap);

      virtual e_line_join get_line_join();
      virtual bool set_line_join(e_line_join elinejoin);

      pen & operator = (const pen & penSrc);


      virtual void dump(dump_context & dumpcontext) const;


   };


   class CLASS_DECL_ca2 pen_sp :
      virtual public ::ca::smart_pointer < pen >
   {
   public:

      pen_sp()
      {
      }

      pen_sp(const ::ca::smart_pointer < pen > & p) :
         ::ca::smart_pointer < pen > (p)
      {
      }

      pen_sp(allocatorsp allocer) :
         ::ca::smart_pointer < pen > (allocer)
      {
      }

      pen_sp(::ca2::graphics * pgraphics, double dWidth, COLORREF crColor);
/*
      pen_sp(sp(::ca2::application) papp, int32_t nPenStyle, int32_t nWidth, const LOGBRUSH* pLogBrush,
         int32_t nStyleCount = 0, const uint32_t* lpStyle = NULL) :
         ::ca::smart_pointer < pen > (papp)
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


} // namespace ca2
