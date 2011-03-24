#pragma once

namespace mail
{

   class CLASS_DECL_ca application : 
      virtual public ::ca84::application
   {
   public:
      
      tree *                                          m_pmailtree;
      list *                                          m_pmaillist;
      main_view *                                     m_pmainview;
      right_pane_view *                               m_prightpaneview;
      right_view *                                    m_prightview;
      ::userbase::single_document_template *          m_ptemplate_html;
      array_ptr < mail::account, mail::account & >    m_accounta;

      application();
      virtual ~application();

      void InitializeMail();
      
      void TimerStep();

      bool initialize_instance();

      BOOL exit_instance();

      void _001OnFileNew();

      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };

} // namespace mail