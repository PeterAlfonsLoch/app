#pragma once

namespace html
{

class document
{
public:
   BaseArrayPtrAlloc < font, font > m_fonta;


   XNode m_node;

   elemental m_elemental;

   void load(const char *);
   void implement(CDC * pdc);
   void _001OnDraw(CDC * pdc);


   base_wnd *  m_pwnd;
   Ex1VirtualGuieInterface * m_pguie;
   CDC *       m_pdc;
   BaseRect    m_rect;

   font * get_font(elemental * pelemental);
protected:
   int create_font(elemental * pelemental);

};


} // namespace html