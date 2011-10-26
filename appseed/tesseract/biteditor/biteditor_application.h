#pragma once



class CLASS_DECL_CA2_TESSERACT biteditor_application :
   public ::winservice_filesystemsize::application
{
public:


   ::userbase::document_template * m_ptemplateEdge;
   ::userbase::document_template * m_ptemplate_devedge;
   ::userbase::document_template * m_ptemplateFront;

   
   biteditor_application(void);
   virtual ~biteditor_application(void);

   virtual void construct();

   virtual void on_request(::ca::create_context * pcreatecontext);

   bool initialize_instance();


};



