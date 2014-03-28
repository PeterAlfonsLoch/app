#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE table : public elemental
      {
      public:


         class CLASS_DECL_CORE column
         {
         public:

            index        m_iCol;
            float        m_cxMax;
            float        m_cxMin;

            column();
            column(index iCol);

         };

         float                                           m_iBorder;
         float                                           m_iCellSpacing;
         float                                           m_iCellPadding;

         array < array < cell::holder > >    m_cellholdera;
         comparable_array < table_row * >                m_rowptra;
         array < column >                          m_columna;

         
         table();
         virtual ~table();


         void set_cell(index iCol, index iRow, cell * pcell);

         virtual void implement_phase2(data * pdata);
         virtual void layout_phase3(data * pdata);

         void _001OnDraw(data * pdata);

         void implement_phase1(data * pdata, ::html::elemental * pelemental);

         void final_layout(data * pdata);


      };


   } // namespace impl


} // namespace html




