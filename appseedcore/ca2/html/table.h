#pragma once


namespace html
{

namespace impl
{

   class CLASS_DECL_ca table : public elemental
   {
   public:
      table();
      virtual ~table();


      class CLASS_DECL_ca column
      {
      public:
         column();
         int m_cxMax;
         int m_cxMin;
      };

      void set_cell(point pt, cell * pcell);

      virtual void implement_phase2(data * pdata);
      virtual void layout_phase3(data * pdata);

      base_array < base_array < cell::holder > > m_cellholdera;
      base_array < table_row * > m_rowptra;
      base_array < column > m_columna;
   };


} // namespace impl

} // namespace html