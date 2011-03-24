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

class elemental;

namespace impl
{
   class elemental
   {
   public:
      EPosition m_eposition;

      virtual ~elemental();


      virtual int get_x();
      virtual int get_y();
      virtual int get_cx();
      virtual int get_cy();
      virtual void set_x(document * pdoc, int x);
      virtual void set_y(document * pdoc, int y);
      virtual void set_cx(document * pdoc, int cx);
      virtual void set_cy(document * pdoc, int cy);
      virtual void set_xy(document * pdoc, int x, int y);
      virtual void set_cxy(document * pdoc, int cx, int cy);
      virtual void set_pos(document * pdoc, int x, int y, int cx, int cy);

      ::html::elemental * m_pelemental;
      virtual void _001OnDraw(document * pdoc);
      virtual void implement(document * pdoc, ::html::elemental * pelemental);
      virtual void on_change_layout(document * pdoc);
   protected:
      point m_pt;
      size m_size;
   };
} // namespace impl


class elemental
{
public:
   elemental(elemental * pparent = NULL);
   virtual ~elemental();
   // always present property?! "text"
   gen::PropertySet m_propertyset;

   impl::elemental *    m_pimpl;
   elemental *          m_pparent;
   LPXNode              m_pnode;

   style                m_style;

   base_array < elemental *, elemental * > m_elementalptra;
   virtual void implement(document * pdoc);
   virtual void _001OnDraw(document * pdoc);
   virtual void load(document * pdoc, LPXNode pnode);

   bool get_background_color(COLORREF & cr);
protected:
   virtual bool parse(document * pdoc, const char * & psz);
   virtual void parse_attributes(document * pdoc, const char * & psz);
};



} // namespace html