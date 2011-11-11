#pragma once


namespace html
{

   namespace impl
   {
      class table;
      class table_row;

      class CLASS_DECL_ca cell : public text
      {
      public:

         class CLASS_DECL_ca holder
         {
         public:
            holder();
            holder(point pt);
            holder(cell * pcell, point pt);
            holder(const class holder & holder);
            html::impl::cell *   m_pcell;
            point                m_pt;

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
         base_array < point, point & > m_ptaPopulation; 
         
         
         double m_dWidth;
         int m_iWidth;
         int m_iRowSpan;
         int m_iColSpan;


         table * get_table();
         table_row * get_row();
         int get_min_col();

         using text::set_xy;
         void set_xy(data * pdoc);

         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void implement_phase2(data * pdoc);
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase3(data * pdoc);
         virtual void final_layout(data * pdoc);
         void on_change_layout(data * pdoc);
      };


   } // namespace impl

} // namespace html