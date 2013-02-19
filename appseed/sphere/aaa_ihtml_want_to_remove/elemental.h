#pragma once

class html_view;

namespace html
{
   class document;

   enum EProperty
   {
      PropertyTag,
      PropertyBody,
      PropertyText
   };
   enum EPosition
   {
      PositionRelative,
   };

   enum EFlag
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
   class CLASS_DECL_CA2_HTML elemental
   {
   public:
      EPosition m_eposition;
      Flags < EFlag > m_flags;
      int      m_cxMax;
      int      m_cxMin;

      DECL_GEN_SIGNAL(OnLButtonDown)
      DECL_GEN_SIGNAL(OnMouseMove)
      DECL_GEN_SIGNAL(OnLButtonUp)


      elemental();

      virtual ~elemental();

      virtual bool get_color(COLORREF & cr);

      virtual bool has_link();
      virtual string link();

      bool hit_test(point pt);


      virtual int get_x();
      virtual int get_y();
      virtual int get_cx();
      virtual int get_cy();
      virtual int get_first_line_height();
      virtual int get_last_line_height();
      virtual size get_bound_size();
      virtual void set_bound_size(document * pdoc, size size);
      virtual point get_bound_point();
      virtual void set_bound_point(document * pdoc, point point);
      virtual void set_x(document * pdoc, int x);
      virtual void set_y(document * pdoc, int y);
      virtual void set_cx(document * pdoc, int cx);
      virtual void set_cy(document * pdoc, int cy);
      virtual void set_xy(document * pdoc, int x, int y);
      virtual void set_cxy(document * pdoc, int cx, int cy);
      virtual void set_pos(document * pdoc, int x, int y, int cx, int cy);

      ::html::elemental * m_pelemental;
      virtual void _001OnDraw(document * pdoc);

      virtual void implement_phase1(document * pdoc, ::html::elemental * pelemental);
      virtual void implement_phase2(document * pdoc);
      
      
      virtual void layout_phase1(document * pdoc);
      virtual void layout_phase2(document * pdoc);
      virtual void layout_phase3(document * pdoc);

      virtual void final_layout(document * pdoc);
      virtual void set_xy(document * pdoc);

      virtual void on_change_layout(document * pdoc);
   protected:
      point m_pt;
      size m_size;
      point m_ptBound;
      size m_sizeBound;
   };
} // namespace impl


class CLASS_DECL_CA2_HTML elemental
{
public:
   elemental(elemental * pparent = NULL);
   virtual ~elemental();
   // always present property?! "text"
   gen::PropertySet     m_propertyset;

   DECL_GEN_SIGNAL(OnLButtonDown)
   DECL_GEN_SIGNAL(OnMouseMove)
   DECL_GEN_SIGNAL(OnLButtonUp)

   impl::elemental *    m_pimpl;
   elemental *          m_pparent;
   base *               m_pbase;

   style                m_style;

   elemental * get_element_by_name(const char * pszName);

   virtual elemental * hit_test(point pt);

   base_array < elemental *, elemental * > m_elementalptra;
   virtual void implement(document * pdoc);
   virtual void layout(document * pdoc);
   
   virtual void _001OnDraw(document * pdoc);
   virtual void load(document * pdoc, base * pbase);

   bool get_background_color(COLORREF & cr);
   bool get_color(COLORREF & cr);


   virtual void implement_phase1(document * pdoc);
   virtual void implement_phase2(document * pdoc);

   virtual void layout_phase1(document * pdoc);
   virtual void layout_phase2(document * pdoc);
   virtual void layout_phase3(document * pdoc);

protected:
   virtual bool parse(document * pdoc, const char * & psz);
   virtual void parse_attributes(document * pdoc, const char * & psz);
};



} // namespace html