#pragma once

namespace paint
{

class document : virtual public ::radix::object
{
public:
   array_ptr_alloc < html::font, html::font > m_fonta;

   document(::ca::application * papp);

   xml::node m_node;

   elemental m_elemental;

   void load(const char *);
   void implement(::ca::graphics * pdc);
   void _001OnDraw(::ca::graphics * pdc);


   ::user::interaction *  m_pwnd;
   ::user::interaction * m_pguie;
   ::ca::graphics *       m_pdc;
   rect    m_rect;

   html::font * get_font(elemental * pelemental);
protected:
   int create_font(elemental * pelemental);

};


} // namespace paint