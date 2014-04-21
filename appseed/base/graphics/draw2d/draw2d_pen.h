#pragma once


namespace draw2d
{


   class CLASS_DECL_BASE pen :
      virtual public ::draw2d::object
   {
   public:


      enum e_type
      {
         
         type_null,
         type_solid
            
      };

      
      enum e_end_cap
      {
         
         end_cap_flat,
         end_cap_round
            
      };


      enum e_line_join
      {
         
         line_join_miter,
         line_join_bevel,
         line_join_round,
         line_join_miter_clipped
            
      };
      

      e_type            m_etype;
      e_end_cap         m_eendcap;
      e_line_join       m_elinejoin;
      double            m_dWidth;
      COLORREF          m_cr;


      pen();
      virtual ~pen();


      virtual bool create_null();
      virtual bool create_solid(double dWidth, COLORREF crColor);

      virtual e_end_cap get_end_cap();
      virtual bool set_end_cap(e_end_cap eendcap);

      virtual e_line_join get_line_join();
      virtual bool set_line_join(e_line_join elinejoin);

      pen & operator = (const pen & penSrc);


      virtual void dump(dump_context & dumpcontext) const;


   };


   class CLASS_DECL_BASE pen_sp :
      public smart_pointer < pen >
   {
   public:

      pen_sp()
      {
      }

      pen_sp(pen * ppen) :
         smart_pointer < pen > (ppen)
      {
      }

      pen_sp(const smart_pointer < pen > & p) :
         smart_pointer < pen > (p)
      {
      }

      pen_sp(allocatorsp allocer) :
         smart_pointer < pen > (allocer)
      {
      }

      pen_sp(::draw2d::graphics * pgraphics, double dWidth, COLORREF crColor);
/*
      pen_sp(sp(base_application) papp, int32_t nPenStyle, int32_t nWidth, const LOGBRUSH* pLogBrush,
         int32_t nStyleCount = 0, const uint32_t* lpStyle = NULL) :
         smart_pointer < pen > (papp)
      {
         m_p->construct(nPenStyle, nWidth, pLogBrush, nStyleCount, lpStyle);
      }
*/


      pen_sp & operator = (::draw2d::pen * ppen)
      {

         smart_pointer < pen >::operator = (ppen);

         return *this;

      }


   };


} // namespace draw2d





