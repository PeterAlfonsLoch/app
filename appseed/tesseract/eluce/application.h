#pragma once

namespace eluce
{
   
   class pane_view;

   class CLASS_DECL_CA2_TESSERACT application :
      public ::biteditor_application
   {
   public:
      
      
      pane_view *                                  m_ppaneview;
      ::userbase::single_document_template *       m_ptemplateMain;
      ::userbase::single_document_template *       m_ptemplateImage;


      application(void);
      virtual ~application(void);


      virtual void construct();


      virtual bool initialize_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);

   };

} // namespace eluce
