#pragma once

namespace syllomatter
{

   class CLASS_DECL_CA2_CUBE application :
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

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);


      virtual void create(const char * psz);
      virtual void commit(const char * pszDescriptor, const char * pszWorkingCopy);
      virtual void checkout(const char * pszRepos, const char * pszWorkingCopy);
      virtual void update(const char * pszWorkingCopy);

   };

} // namespace syllomatter

