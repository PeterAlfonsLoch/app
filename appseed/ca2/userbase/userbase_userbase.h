#pragma once


namespace userbase
{


   class front_end_schema;
   class document_manager;
   class document_template;
   class document;


   class CLASS_DECL_ca2 userbase :
      virtual public ::ca::section,
      virtual public BaseMenuCentralContainer,
      virtual public ::database::client
   {
   public:

      
      ::user::front_end_schema *   m_pufeschema;
      ::user::front_end *           m_pufe;


      userbase();
      virtual ~userbase();


      virtual void AddToRecentFileList(const char * lpszPathName);

      ::user::front_end_schema * GetUfeSchema();
      ::user::front_end * GetUfe();

      virtual bool initialize();
      virtual bool finalize();

      virtual void _001CloseAllDocuments(bool bEndSession);
      void add_document_template(sp(::userbase::document_template) ptemplate);
      virtual sp(::userbase::document) _vmsguserbaseOpenDocumentFile(const char * lpszFileName);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      virtual void _001OnFileNew();


      void defer_add_document_template(sp(::document_template) ptemplate);
      

   };


   CLASS_DECL_ca2 ::user::front_end_schema * GetUfeSchema(sp(::ca::application) papp);
   CLASS_DECL_ca2 ::user::front_end * GetUfe(sp(::ca::application) papp);



} // namespace userbase


