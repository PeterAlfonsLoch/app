#pragma once



namespace filemanager
{


   class CLASS_DECL_ca2 filemanager :
      virtual public ::base_departament,
      virtual public FileManagerCallbackInterface,
      virtual public FileManagerFileListCallback,
      virtual public ::database::client
   {
   public:


      FileManagerTemplate *                        m_ptemplateStd;
      FileManagerTemplate *                        m_ptemplateFs;
      sp(::user::multiple_document_template)     m_ptemplateForm;
      sp(::user::single_document_template)       m_ptemplateOperation;

      string                                       m_strCopy;
      id                                           m_idFileManager;


      filemanager(base_application * papp);
      virtual ~filemanager();

      bool initialize();


      virtual void InitializeFileManager(const char * pszMatter);
      
      
      inline FileManagerTemplate & std()     { return *m_ptemplateStd   ; }
      inline FileManagerTemplate & fs()      { return *m_ptemplateFs    ; }


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);





      virtual bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(::user::document_template) ptemplate, sp(::user::document_interface) pdocument);

      string get_initial_browse_path(const char * pszDefault = NULL);


      virtual void on_request(sp(::create_context) pcreatecontext);


   };



} // namespace filemanager


