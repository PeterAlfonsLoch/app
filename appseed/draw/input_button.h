#pragma once


namespace html
{

namespace impl
{

   class input_button : public elemental
   {
   public:

      int m_iFont;
      Ex1Button * m_pbutton;
      input_button();
      virtual ~input_button();
      void _001OnDraw(document * pdoc);
      void implement(document * pdoc, ::html::elemental * pelemental);
      void on_change_layout(document * pdoc);
   };

} // namespace visual

} // namespace html