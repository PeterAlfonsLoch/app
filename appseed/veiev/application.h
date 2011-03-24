#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV application :
      public ::cube::application
   {
   public:


      ::veiev::list *                           m_pveievlist;
      ::veiev::second_command_view *            m_pmainview;
      ::veiev::right_pane_view *                m_prightpaneview;
      ::veiev::right_view *                     m_prightview;
      ::veiev::tree *                           m_pveievtree;
      ::userbase::single_document_template *    m_ptemplate_html;
      ::userbase::single_document_template *    m_ptemplateVeiev;



      application(void);
      virtual ~application(void);

      bool initialize_instance();
      BOOL exit_instance();


	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      virtual void _001OnFileNew();
   		

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace veiev