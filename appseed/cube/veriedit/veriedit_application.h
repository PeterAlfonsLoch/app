#pragma once

namespace veriedit
{

   class pane_view;

   class CLASS_DECL_CA2_CUBE application :
      virtual public ::syllomatter::application
   {
   public:

      pane_view *                               m_ppaneview;
      ::userbase::single_document_template *    m_ptemplateMain;
      ::userbase::multiple_document_template *  m_ptemplateEdit;

      application(void);
      virtual ~application(void);

      virtual void construct();

      bool initialize_instance();
      BOOL exit_instance();

      virtual void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      ::document * _001OpenDocumentFile(var varFile);
      void _001OnFileNew();

      virtual bool on_install();
   };


} // namespace devedge