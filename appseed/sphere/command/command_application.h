#pragma once


namespace command
{


   class CLASS_DECL_sphere application :
      virtual public ::filehandler::application
   {
   public:


      sp(::user::single_document_template)    m_ptemplateCommandMain;


      application();
      virtual ~application();


      void construct();


      bool initialize_instance();
      virtual int32_t exit_instance();


	   virtual bool _001OnCmdMsg(::base::cmd_msg * pcmdmsg);


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace command