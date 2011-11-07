#pragma once

namespace syllomatter
{

   class CLASS_DECL_CA2_TESSERACT application :
      virtual public ::verisimplevideo::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;



      application();
      virtual ~application(void);

      void construct();

      virtual void InitializeFileManager(const char * pszMatter);

      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);


      virtual void OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, const ::fs::item & item, stringa & straCommand, stringa & straCommandTitle);



      using ::ex1::request_interface::create;
      virtual void create(const char * psz);
      virtual void commit(const char * pszDescriptor, const char * pszWorkingCopy);
      virtual void checkout(const char * pszRepos, const char * pszWorkingCopy);
      virtual void update(const char * pszWorkingCopy);


      DECL_GEN_SIGNAL(_001OnAddWorkingCopy)

   };

} // namespace syllomatter

