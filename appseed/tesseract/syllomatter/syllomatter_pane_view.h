#pragma once

#include "syllomatter_pane_view_update_hint.h"

class CLASS_DECL_CA2_TESSERACT syllomatter_pane_view : 
   virtual public ::userex::pane_tab_view
{
public:
   
   ::userbase::single_document_template *    m_pdoctemplateExtractChanges;
   ::filemanager::document *                          m_pfilemanagerdoc;
   svn_view *                                m_psvnview;
   syllomatter_document *                    m_pdocForm;
   syllomatter_view  *                       m_pviewForm;

   syllomatter_pane_view(::ca::application * papp);
   virtual ~syllomatter_pane_view();

   
   virtual void on_create_view(::user::view_creator_data * pcreatordata);
   virtual void on_show_view();

   virtual void install_message_handling(::user::win::message::dispatch * pinterface);

   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   DECL_GEN_SIGNAL(_001OnMenuMessage)
   DECL_GEN_SIGNAL(_001OnStartVerisvnwellExtract)
   DECL_GEN_SIGNAL(_001OnCommit_)
   DECL_GEN_SIGNAL(_001OnUpdate)


#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   DECL_GEN_SIGNAL(_001OnCreate)
};

