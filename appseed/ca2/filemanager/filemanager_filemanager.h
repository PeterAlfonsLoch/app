#pragma once



namespace filemanager
{


   class CLASS_DECL_ca2 filemanager :
      virtual public ::ca::section,
      virtual public FileManagerCallbackInterface,
      virtual public FileManagerFileListCallback,
      virtual public ::database::client
   {
   public:


      FileManagerTemplate *                        m_ptemplateStd;
      FileManagerTemplate *                        m_ptemplateFs;
      ::userbase::multiple_document_template *     m_ptemplateForm;
      sp(::userbase::single_document_template)       m_ptemplateOperation;

      string                                       m_strCopy;
      id                                           m_idFileManager;


      filemanager();
      virtual ~filemanager();

      bool initialize();


      virtual void InitializeFileManager(const char * pszMatter);
      
      
      inline FileManagerTemplate & std()     { return *m_ptemplateStd   ; }
      inline FileManagerTemplate & fs()      { return *m_ptemplateFs    ; }


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);





      virtual bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(document_template) ptemplate, sp(::user::document_interface) pdocument);

      string get_initial_browse_path(const char * pszDefault = ::null());


      virtual void on_request(sp(::ca::create_context) pcreatecontext);


   };



} // namespace filemanager


