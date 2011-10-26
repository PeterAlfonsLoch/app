#pragma once

namespace veriedit
{

   class pane_view;

   class CLASS_DECL_CA2_TESSERACT application :
      virtual public ::syllomatter::application
   {
   public:

      pane_view *                               m_ppaneview;
      ::userbase::single_document_template *    m_ptemplateMain;
      ::userbase::multiple_document_template *  m_ptemplateEdit;

      application(void);
      virtual ~application(void);

      virtual void construct();

      bool initialize_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);

      virtual bool on_install();
   };


} // namespace devedge