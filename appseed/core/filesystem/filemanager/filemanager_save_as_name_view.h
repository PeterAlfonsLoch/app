#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE save_as_edit_view :
      virtual public ::user::show < ::user::plain_edit >,
      virtual public ::filemanager::impact
   {
   public:

      bool m_bVoidSync;


      save_as_edit_view(::aura::application * papp);


      virtual void _001OnAfterChangeText(::action::context actioncontext);


      void on_update(::user::impact * pSender, LPARAM lHint, object* phint);


      virtual void browse_sync(::action::context actioncontext);

   };

   class CLASS_DECL_CORE save_as_button :
      virtual public ::user::show < ::user::button >,
      virtual public ::filemanager::impact
   {
   public:

      save_as_button(::aura::application * papp);

      virtual bool _001OnClick(uint_ptr nFlag, point point) override;
      void on_update(user::impact *, LPARAM, object *);

   };

   class CLASS_DECL_CORE save_as_view:
      virtual public ::user::split_view,
      virtual public ::filemanager::impact
   {
   public:


      save_as_edit_view *     m_pedit;
      save_as_button *        m_pbutton;

      
      save_as_view(::aura::application * papp);


      void on_update(::user::impact * pSender,LPARAM lHint,object* phint);


      virtual void on_create_views();

   };


} // namespace filemanager





