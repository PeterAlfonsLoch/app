#pragma once


namespace paint
{

namespace impl
{

   class input_button : public elemental
   {
   public:

      int m_iFont;
      ::user::button * m_pbutton;
      input_button(document * pdoc);
      virtual ~input_button();
      void _001OnDraw(document * pdoc);
      void implement(document * pdoc, ::paint::elemental * pelemental);
      void on_change_layout(document * pdoc);
   };

} // namespace visual

} // namespace paint