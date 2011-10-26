#pragma once

namespace veriedit
{

   class document;

   class CLASS_DECL_CA2_TESSERACT pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:

      ::filemanager::document *                 m_pfilemanagerdoc;
      ::filemanager::document *                 m_pfilemanagerdocFs;
      ::userbase::single_document_template *    m_pdoctemplateExtractChanges;

      pane_view(::ca::application * papp);
      virtual ~pane_view();

   
      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void on_show_view();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


      virtual document * get_veriedit_document(const char * pszUrl);

      virtual void get_opened_documents(stringa & stra);

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
   };

} // namespace veriedit