#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_ca2 table : public elemental
      {
      public:


         class CLASS_DECL_ca2 column
         {
         public:

            index        m_iCol;
            int32_t      m_cxMax;
            int32_t      m_cxMin;

            column();
            column(index iCol);

         };

         float                                         m_iBorder;
         float                                         m_iCellSpacing;
         float                                         m_iCellPadding;

         base_array < base_array < cell::holder > >   m_cellholdera;
         comparable_array < table_row * >             m_rowptra;
         base_array < column >                        m_columna;

         
         table();
         virtual ~table();


         void set_cell(int32_t iCol, int32_t iRow, cell * pcell);

         virtual void implement_phase2(data * pdata);
         virtual void layout_phase3(data * pdata);

         void _001OnDraw(data * pdata);

         void implement_phase1(data * pdata, ::html::elemental * pelemental);

         void final_layout(data * pdata);


      };


   } // namespace impl


} // namespace html




