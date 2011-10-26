#pragma once


namespace paint
{

namespace impl
{

   class input_text : public elemental
   {
   public:
      int m_iFont;
      ::user::edit_plain_text * m_pedit;
      input_text(document * pdoc);
      virtual ~input_text();
      void _001OnDraw(document * pdoc);
      void implement(document * pdoc, ::paint::elemental * pelemental);
      void on_change_layout(document * pdoc);
   };

} // namespace visual

} // namespace paint