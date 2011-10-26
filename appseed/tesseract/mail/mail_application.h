#pragma once


namespace tesseract
{

   namespace mail
   {

      class CLASS_DECL_CA2_TESSERACT application : 
         virtual public ::whiteboard::application
      {
      public:
      
         tree *                                          m_pmailtree;
         list *                                          m_pmaillist;
         main_view *                                     m_pmainview;
         right_pane_view *                               m_prightpaneview;
         right_view *                                    m_prightview;
         ::userbase::single_document_template *          m_ptemplate_html;
         array_del_ptr < ::mail::account, ::mail::account & >    m_accounta;

         application();
         virtual ~application();

         void InitializeMail();
      
         void TimerStep();

         bool initialize_instance();

         BOOL exit_instance();

         void _001OnFileNew();

         virtual void update_pop3_mail_lists();

      };

   } // namespace mail


} // namespace tesseract


