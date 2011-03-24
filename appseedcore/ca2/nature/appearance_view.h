#pragma once

class ::userbase::single_document_template;
class view;
class create_context;

namespace nature
{

   class CLASS_DECL_ca appearance_view : 
      public ::userex::pane_tab_view
   {
   public:


      enum e_view
      {
         view_image_folder,
      };


      appearance_view(::ca::application * papp);

#if !core_level_1
      using ::userbase::tab_view::on_show_view;
#endif

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual void on_show_view();

      void on_create_view(view_data * pviewdata);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual ~appearance_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnEditAdd)
      DECL_GEN_SIGNAL(_001OnEditRemove)

   };

} // namespace nature