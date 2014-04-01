#pragma once


namespace html
{


   class CLASS_DECL_CORE elemental : public text_interface
   {
   public:


      // always present property?! "text"
      property_set     m_propertyset;
      impl::elemental *    m_pimpl;
      elemental *          m_pparent;
      base *               m_pbase;
      data *               m_pdata;
      //bool                 m_bHasChar;

      style                m_style;
      array < elemental *, elemental * > m_elementalptra;

      e_tag                m_etag;
      string               m_strBody;
      id                   m_idTagName;
      bool                 m_bParent;
      bool                 m_bTagVisible;
      string               m_strClass;
      string               m_strInlineStyle;


      elemental(data * pdoc, elemental * pparent = NULL);
      virtual ~elemental();

      virtual void _001SetText(const string & str, ::action::context actioncontext);

      DECL_GEN_SIGNAL(OnLButtonDown)
      DECL_GEN_SIGNAL(OnMouseMove)
      DECL_GEN_SIGNAL(OnLButtonUp)


      virtual void delete_implementation();

      
      

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

      static bool tag_visible(e_tag etag);

      void initialize();

      tag * get_tag();


      virtual void implement_phase1(data * pdoc);
      virtual void implement_phase2(data * pdoc);

      virtual void layout_phase0(data * pdata); // cx min/max
      virtual void layout_phase1(data * pdata); // cxy
      virtual void layout_phase2(data * pdata); // adjust
      virtual void layout_phase3(data * pdata); // final layout

      virtual void get_html(data * pdata, string & str);


   protected:
      virtual bool parse(data * pdoc, const char * & psz);
      virtual void parse_attributes(data * pdoc, const char * & psz);


   };


} // namespace html





