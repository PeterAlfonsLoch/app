#pragma once


namespace veriview
{

   class a_view;

   class CLASS_DECL_CA2_TESSERACT application :
      virtual public ::devedge::application
   {
   public:


      ::userbase::single_document_template *       m_ptemplate_main;
      ::userbase::multiple_document_template *     m_ptemplate_html;
      ::userbase::single_document_template *       m_ptemplate_html_edit;
      ::userbase::document_template *              m_ptemplate_devedge;
      
      main_document *                              m_pmaindocument;
      a_view *                                     m_paview;


      application(void);
      virtual ~application(void);


      virtual void construct();


      virtual bool initialize_instance();
      virtual int  exit_instance();

        
      virtual void on_request(::ca::create_context * pcreatecontext);

   };

} // namespace veriview
