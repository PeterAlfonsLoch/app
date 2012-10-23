#pragma once

class html_view;

namespace html
{

   enum e_position
   {
      PositionRelative,
   };

   enum e_flag
   {
      // the width can be expanded
      FlagWidthExpandable,
      // the height can be expanded
      FlagHeightExpandable,
      // the width is fixed but can grow to make space to a single long word
      FlagWidthFixedTable,
      // the width is fixed
      FlagWidthFixed,
      // the height is fixed
      FlagHeightFixed,
      // width in percent
      FlagWidthPercent,
      // width in pixel
      FlagWidthPixel,
      FlagWidth, 
   };


   class elemental;

   namespace impl
   {
      class CLASS_DECL_ca2 elemental
      {
      public:

         box               m_box;
         box               m_bound;
         box               m_padding;
         border            m_border;
         box               m_margin;


         e_position        m_eposition;
         flags < e_flag >  m_flags;
         int               m_cxMax;
         int               m_cxMin;
         ::collection::string_map < int, int > m_mapFont;
         bool              m_bHoverEvaluated;
         bool              m_bHasHover;
         bool              m_bHover;



         DECL_GEN_VSIGNAL(OnLButtonDown)
         DECL_GEN_VSIGNAL(OnMouseMove)
         DECL_GEN_VSIGNAL(OnLButtonUp)

         virtual void delete_implementation();


         elemental();

         virtual ~elemental();

         virtual bool get_color(COLORREF & cr);

         virtual bool has_link();
         virtual string link();

         bool hit_test(data * pdata, ::point pt);
         double bound_hit_test(data * pdata, ::point pt);


         virtual float get_x();
         virtual float get_y();
         virtual float get_cx();
         virtual float get_cy();
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

         ::html::elemental * m_pelemental;
         virtual void _001OnDraw(data * pdoc);

         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void implement_phase2(data * pdoc);
         
         
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase2(data * pdoc);
         virtual void layout_phase3(data * pdoc);

         virtual void final_layout(data * pdoc);
         virtual void set_xy(data * pdoc);

         virtual void on_change_layout(data * pdoc);

         virtual int calc_width();
         virtual bool use_in_final_layout(::html::impl::elemental * pimplChild);

         virtual bool is_tag();
         virtual bool is_value();

      };
   } // namespace impl


   class CLASS_DECL_ca2 elemental : public text_interface
   {
   public:
      elemental(data * pdoc, elemental * pparent = NULL);
      virtual ~elemental();
      // always present property?! "text"
      gen::property_set     m_propertyset;

      virtual void _001SetText(const char * psz);

      DECL_GEN_SIGNAL(OnLButtonDown)
      DECL_GEN_SIGNAL(OnMouseMove)
      DECL_GEN_SIGNAL(OnLButtonUp)


      virtual void delete_implementation();

      impl::elemental *    m_pimpl;
      elemental *          m_pparent;
      base *               m_pbase;
      data *               m_pdata;


      style                m_style;
      base_array < elemental *, elemental * > m_elementalptra;


      elemental * get_element_by_name(id id);
      elemental * get_element_by_id(id id);

      virtual elemental * hit_test(data * pdoc, ::point pt);
      virtual elemental * bound_hit_test(data * pdoc, ::point pt);
      virtual elemental * bound_hit_test(data * pdoc, ::point pt, double & dMin);

      
      virtual void implement(data * pdoc);
      virtual void layout(data * pdoc);
      
      virtual void _001OnDraw(data * pdoc);
      virtual void load(data * pdoc, base * pbase);

      bool get_background_color(COLORREF & cr) const;
      bool get_color(COLORREF & cr) const;

      string get_tag_name() const;
      tag * get_tag();
      const tag * get_tag() const;


      virtual void implement_phase1(data * pdoc);
      virtual void implement_phase2(data * pdoc);

      virtual void layout_phase1(data * pdoc);
      virtual void layout_phase2(data * pdoc);
      virtual void layout_phase3(data * pdoc);

      virtual void get_html(data * pdata, string & str) const;

   protected:
      virtual bool parse(data * pdoc, const char * & psz);
      virtual void parse_attributes(data * pdoc, const char * & psz);
   };



} // namespace html