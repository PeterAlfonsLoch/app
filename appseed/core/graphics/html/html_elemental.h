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
      // the width is fixed but can grow to make space to a single long uint16_t
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

      class elemental;

   } // namespace impl

   class CLASS_DECL_CORE elemental : public text_interface
   {
   public:
      elemental(data * pdoc, elemental * pparent = NULL);
      virtual ~elemental();
      // always present property?! "text"
      property_set     m_propertyset;

      virtual void _001SetText(const string & str, ::action::context actioncontext);

      DECL_GEN_SIGNAL(OnLButtonDown)
      DECL_GEN_SIGNAL(OnMouseMove)
      DECL_GEN_SIGNAL(OnLButtonUp)


      virtual void delete_implementation();

      impl::elemental *    m_pimpl;
      elemental *          m_pparent;
      base *               m_pbase;
      data *               m_pdata;


      style                m_style;
      array < elemental *, elemental * > m_elementalptra;


      elemental * get_element_by_name(id id);
      elemental * get_element_by_id(id id);

      virtual elemental * hit_test(data * pdoc, ::point pt);
      virtual elemental * bound_hit_test(data * pdoc, ::point pt);
      virtual elemental * bound_hit_test(data * pdoc, ::point pt, double & dMin);


      virtual void implement(data * pdoc);
      virtual void layout(data * pdoc);

      virtual void _001OnDraw(data * pdoc);
      virtual void load(data * pdoc, base * pbase);

      bool get_background_color(COLORREF & cr);
      bool get_color(COLORREF & cr);

      string get_tag_name();
      tag * get_tag();


      virtual void implement_phase1(data * pdoc);
      virtual void implement_phase2(data * pdoc);

      virtual void layout_phase1(data * pdoc);
      virtual void layout_phase2(data * pdoc);
      virtual void layout_phase3(data * pdoc);

      virtual void get_html(data * pdata, string & str);

   protected:
      virtual bool parse(data * pdoc, const char * & psz);
      virtual void parse_attributes(data * pdoc, const char * & psz);
   };



} // namespace html
