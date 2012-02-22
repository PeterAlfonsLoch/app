#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_ca2 table_row : public elemental
      {
      public:

         index   m_iIndex;
         int   m_cyMin;
         int   m_cyMax;

         table * get_table();

         void set_cell(point pt, cell * pcell);


         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void implement_phase2(data * pdoc);
         virtual void layout_phase3(data * pdata);
         virtual void final_layout(data * pdata);

         base_array < cell::holder > m_cellholdera;

         table_row();
         virtual ~table_row();


      };


   } // namespace impl


} // namespace html

