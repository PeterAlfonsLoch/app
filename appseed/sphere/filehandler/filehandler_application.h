#pragma once


namespace filehandler
{


   class CLASS_DECL_sphere application :
      virtual public ::calculator::application
   {
   public:


      sp(pane_view)                                  m_ppaneview;      
      sp(::user::single_document_template)       m_ptemplateMenu;


      application();
      virtual ~application();

      virtual void construct();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();


      virtual void on_request(sp(::create) pcreatecontext);


   };


} // namespace filehandler


