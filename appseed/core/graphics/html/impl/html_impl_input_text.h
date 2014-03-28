#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE input_text : public elemental
      {
      public:
         int32_t m_iFont;
         ::user::edit_plain_text * m_pedit;
         input_text(data * pdoc);
         virtual ~input_text();
         void _001OnDraw(data * pdoc);
         virtual void implement_phase1(data * pdoc, ::html::elemental * pelemental);
         virtual void layout_phase1(data * pdoc);
         virtual void layout_phase3(data * pdoc);
         void on_change_layout(data * pdoc);
      };


   } // namespace impl


} // namespace html





