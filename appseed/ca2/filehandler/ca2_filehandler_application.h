#pragma once


namespace ca2
{


   namespace filehandler
   {


      class CLASS_DECL_ca2 application :
         virtual public ::cube2::application
      {
      public:


         pane_view *                                  m_ppaneview;      
         ::userbase::single_document_template *       m_ptemplateMenu;


         application(void);
         virtual ~application(void);

         virtual void construct();

         virtual bool initialize_instance();
         virtual int exit_instance();


         virtual void on_request(::ca::create_context * pcreatecontext);


      };


   } // namespace filehandler


} // namespace mail


