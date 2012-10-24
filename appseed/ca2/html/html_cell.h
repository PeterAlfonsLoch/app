#pragma once


namespace html
{


   namespace impl
   {


      class table;
      class table_row;


      class CLASS_DECL_ca2 cell : public text
      {
      public:


         class CLASS_DECL_ca2 holder
         {
         public:

            
            int m_iCol;
            int m_iRow;


            holder();
            holder(int iCol, int iRow);
            holder(cell * pcell, int iCol, int iRow);
            holder(const class holder & holder);
            ::html::impl::cell *   m_pcell;

            bool is_null();

            holder & operator = (const class holder & holder);


         };

         cell(::ca::application * papp);
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
         int m_iColBeg;
         int m_iRowBeg;
         int m_iColEnd;
         int m_iRowEnd;
         
         
         double m_dWidth;
         int m_iWidth;
         int m_iRowSpan;
         int m_iColSpan;


         table * get_table();
         table_row * get_row();
         int get_min_col();

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


         virtual int calc_width();


         virtual bool contains_column(int iCol);
         virtual bool contains_row(int iRow);
         virtual bool contains_cell(int iCol, int iRow);

         virtual float get_table_border();
         virtual float get_cell_spacing();
         virtual float get_cell_padding();


      };


   } // namespace impl

} // namespace html