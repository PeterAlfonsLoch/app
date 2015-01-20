#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC edit_view:
      virtual public ::user::edit_plain_text_view
   {
   public:


      top_view * m_ptopview;


      edit_view(::aura::application * papp);
      virtual ~edit_view();

      virtual void _001OnAfterChangeText(::action::context actioncontext);

      void on_update(::aura::impact * pSender,LPARAM lHint,object* phint);

      bool keyboard_focus_is_focusable();

      virtual int64_t add_ref();

      virtual int64_t dec_ref();

   };


} // namespace turboc




