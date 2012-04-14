#pragma once



namespace filemanager
{


   class CLASS_DECL_ca2 application :
      virtual public ::ca8::application,
      virtual public FileManagerCallbackInterface,
      virtual public FileManagerFileListCallback
   {
   public:


      FileManagerTemplate *            m_ptemplateStd;
      FileManagerTemplate *            m_ptemplateFs;
      ::userbase::multiple_document_template *   m_ptemplateForm;
      ::userbase::single_document_template *     m_ptemplateOperation;

      string                  m_strCopy;


      application();
      virtual ~application();

      bool initialize();

      virtual void on_request(::ca::create_context * pcreatecontext);

      virtual void InitializeFileManager(const char * pszMatter);
      virtual FileManagerTemplate * GetStdFileManagerTemplate(void);
      virtual FileManagerTemplate * GetFsManagerTemplate(void);


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);


      virtual BOOL do_prompt_file_name(var & varFile, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, document_template * ptemplate, ::user::document_interface * pdocument);

      string get_file_manager_initial_browse_path(const char * pszDefault = NULL);

   };



} // namespace filemanager


