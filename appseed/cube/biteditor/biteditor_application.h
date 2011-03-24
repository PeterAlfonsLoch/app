#pragma once



class CLASS_DECL_CA2_CUBE biteditor_application :
   public ::winservice_filesystemsize::application
{
public:


   ::userbase::document_template * m_ptemplateEdge;
   ::userbase::document_template * m_ptemplate_devedge;
   ::userbase::document_template * m_ptemplateFront;

   
   biteditor_application(void);
   virtual ~biteditor_application(void);

   virtual void construct();

   virtual bool bergedge_start();

   bool initialize_instance();
   BOOL exit_instance();


   virtual void pre_translate_message(gen::signal_object * pobj);

   virtual void OnFileManagerOpenFile(
      ::filemanager::data * pdata, 
      ::fs::item_array & itema);

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
      

};



