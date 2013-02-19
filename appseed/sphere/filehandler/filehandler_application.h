#pragma once


namespace filehandler
{


   class CLASS_DECL_ca2 application :
      virtual public ::ca2::calculator::application
   {
   public:


      pane_view *                                  m_ppaneview;      
      ::userbase::single_document_template *       m_ptemplateMenu;


      application();
      virtual ~application();

      using ::ca2::calculator::application::construct;
      virtual void construct();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();


      virtual void on_request(::ca::create_context * pcreatecontext);


   };


} // namespace filehandler


