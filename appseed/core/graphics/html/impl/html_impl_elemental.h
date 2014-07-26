#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE elemental
      {
      public:

         ::html::elemental * m_pelemental;
          

         box               m_box;
         box               m_bound;
         box               m_padding;
         border            m_border;
         box               m_margin;


         e_position        m_eposition;
         flags < e_flag >  m_flags;
         float             m_cxMax;
         float             m_cxMin;
         string_map < int32_t, int32_t > m_mapFont;
         bool              m_bHoverEvaluated;
         bool              m_bHasHover;
         bool              m_bHover;

         bool              m_bHasChar;



         elemental();
         virtual ~elemental();


         virtual void delete_implementation();


         virtual bool get_color(COLORREF & cr);

         virtual bool has_link();
         virtual string link();

         virtual index find(elemental * pelemental);

         virtual elemental * get_sibling(index i);

         virtual elemental * get_next_sibling();
         virtual elemental * get_first_sibling();
         virtual elemental * get_previous_sibling();

         bool hit_test(data * pdata, ::point pt);
         double bound_hit_test(data * pdata, ::point pt);


         virtual float get_x();
         virtual float get_y();
         virtual float get_cx();
         virtual float get_cy();

         virtual size get_content_size();
         virtual point get_content_xy();

         virtual float get_table_border();
         virtual float get_cell_spacing();
         virtual float get_cell_padding();

         virtual float get_first_line_height();
         virtual float get_last_line_height();
         virtual size get_bound_size();
         virtual void set_bound_size(data * pdoc, size size);
         virtual point get_bound_point();
         virtual void set_bound_point(data * pdoc, point point);
         virtual void set_x(data * pdoc, float x);
         virtual void set_y(data * pdoc, float y);
         virtual void set_cx(data * pdoc, float cx);
         virtual void set_cy(data * pdoc, float cy);
         virtual void set_xy(data * pdoc, float x, float y);
         virtual void set_cxy(data * pdoc, float cx, float cy);
         virtual void set_pos(data * pdoc, float x, float y, float cx, float cy);

         virtual void _001OnDraw(data * pdoc);


         virtual float get_extra_content_cx();
         virtual float get_extra_content_cy();


         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void implement_phase2(data * pdoc);


         virtual void container_raw_cxmax(data * pdata);


         virtual void layout_phase0(data * pdata); // cx min/max calculation
         virtual void layout_phase1(data * pdata); // cx calculation or cxy calculation at final nodes
         virtual void layout_phase2(data * pdata); // adjust
         virtual void layout_phase3(data * pdata); // final layout


         virtual void layout_phase0_end(data * pdata); // cxMax calculation for containers
         virtual void layout_phase1_end(data * pdata); // cy calculation
         virtual void layout_phase3_end(data * pdata); // final layout

         virtual void set_xy(data * pdoc);

         virtual void on_change_layout(data * pdoc);

         virtual float calc_width();
         virtual bool use_in_final_layout(::html::impl::elemental * pimplChild);

         virtual bool is_tag();
         virtual bool is_value();


         DECL_GEN_VSIGNAL(OnLButtonDown);
         DECL_GEN_VSIGNAL(OnMouseMove);
         DECL_GEN_VSIGNAL(OnLButtonUp);

         


      };


   } // namespace impl


} // namespace html





