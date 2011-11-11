#pragma once


namespace rtprx
{


   class CLASS_DECL_ca application :
      virtual public ::ca2::filehandler::application
   {
   public:


      class rtprx_start
      {
      public:
		  rtprx_start();
         rtprx::application * m_papp;
         string m_strHost;
         int m_iPort;
         int m_iMode;
		 ::ex1::file * m_pfile;
      };


      ::userbase::single_document_template * m_ptemplate_html;
      ::userbase::single_document_template * m_ptemplateVideo;


      application(void);
      virtual ~application(void);

      virtual void construct();

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual void rtprx(const char * pszUrl);
	  virtual void start_rtprx(ex1::file * pfileRawPcm, const char * pszUrl);
	  static UINT thread_proc_rtprx(LPVOID lpparam);
	  bool rtprx(::ex1::file * pfile, const char * pszUrl, int iPort, int iMode);

      virtual void defer_initialize_document_template();
         

      virtual ::ca::application * get_app() const;
      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

      ::document * _001OpenDocumentFile(var varFile);


      virtual void on_request(::ca::create_context * pcreatecontext);


   };


} // namespace rtprx

