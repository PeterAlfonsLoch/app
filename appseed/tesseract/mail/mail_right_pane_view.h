#pragma once


namespace tesseract
{

namespace mail
{

   class document;

   class CLASS_DECL_CA2_TESSERACT right_pane_view : 
      public ::userex::pane_tab_view
   {
   public:

      enum e_pane
      {
         pane_text,
         pane_configuration,
      };

      configuration  m_cfg;
      mail::view *   m_pmailview;


      right_pane_view(::ca::application * papp);
      virtual ~right_pane_view();

      void on_create_view(::user::view_creator_data * pcreatordata);
      void on_show_view();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnShowWindow)

      document * get_document();

   };


   } // namespace mail


} // namespace tesseract


