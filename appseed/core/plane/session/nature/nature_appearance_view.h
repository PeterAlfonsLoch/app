#pragma once



namespace user
{


   class single_document_template;


} // namespace user


namespace nature
{

   class CLASS_DECL_CORE appearance_view :
      public ::userex::pane_tab_view
   {
   public:


      enum e_view
      {
         view_image_folder,
      };


      appearance_view(sp(::base::application) papp);

      using ::user::tab_view::on_show_view;

      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual void on_show_view();

      void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);
      virtual ~appearance_view();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnEditAdd);
      DECL_GEN_SIGNAL(_001OnEditRemove);

   };

} // namespace nature
