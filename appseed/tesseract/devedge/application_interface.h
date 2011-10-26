#pragma once

namespace devedge
{

   class CLASS_DECL_CA2_TESSERACT application_interface :
      virtual public ::ca::application_interface
   {
   public:
      
      
      ::userbase::single_document_template * m_ptemplateEdge;
      ::userbase::document_template * m_ptemplate_devedge;
      ::userbase::document_template * m_ptemplate_solution;
      ::userbase::document_template * m_ptemplateHtmlEdit;
      ::userbase::document_template * m_ptemplateHtml;
      ::userbase::document_template * m_ptemplateFront;


      application_interface();
      virtual ~application_interface();

      void on_application_signal(::radix::application_signal_object * papplicationsignal);
   };

} // devedge