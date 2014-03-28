#pragma once


namespace html
{


   namespace impl
   {


      class table;
      class table_row;


      class CLASS_DECL_CORE cell : 
         public ::html::impl::text
      {
      public:


         class CLASS_DECL_CORE holder
         {
         public:

            
            int32_t m_iCol;
            int32_t m_iRow;


            holder();
            holder(int32_t iCol, int32_t iRow);
            holder(cell * pcell, int32_t iCol, int32_t iRow);
            holder(const class holder & holder);
            ::html::impl::cell *   m_pcell;

            bool is_null();

            holder & operator = (const class holder & holder);


         };

         cell(sp(base_application) papp);
         virtual ~cell();
         // example 1:
         // -------------------
         // |   X    |        |
         // -------------------
         // |        |        |
         // -------------------
         // population: (0, 0)
         // example 2:
         // -----------------------------
         // |        |        |         |
         // -----------------------------
         // |        |                  |        
         // ----------        X         |
         // |        |                  |
         // -----------------------------
         // population: (1, 1), (1, 2), (2, 1), (2, 2)
         index m_iColBeg;
         index m_iRowBeg;
         index m_iColEnd;
         index m_iRowEnd;
         
         
         float m_fWidth;

         ::count m_iRowSpan;
         ::count m_iColSpan;


         table * get_table();
         table_row * get_row();
         index get_min_col();

         using text::set_xy;
         void set_xy(data * pdoc);


         virtual size get_content_size();
         virtual point get_content_xy();


         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void implement_phase2(data * pdoc);
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase3(data * pdoc);
         virtual void final_layout(data * pdoc);
         void on_change_layout(data * pdoc);

         void _001OnDraw(data * pdata);


         virtual float calc_width();


         virtual bool contains_column(index iCol);
         virtual bool contains_row(index iRow);
         virtual bool contains_cell(index iCol, index iRow);

         virtual float get_table_border();
         virtual float get_cell_spacing();
         virtual float get_cell_padding();


      };


   } // namespace impl

} // namespace html