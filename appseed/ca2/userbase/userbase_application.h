#pragma once


namespace userbase
{


   class front_end_schema;
   class document_manager;
   class document_template;
   class document;


   class CLASS_DECL_ca application :
      virtual public ::user::application,
      public BaseMenuCentralContainer
   {
   public:

      ::user::front_end_schema *   m_pufeschema;
      ::user::front_end *           m_pufe;

      application();
      virtual ~application();


      virtual void AddToRecentFileList(const char * lpszPathName);

      ::user::front_end_schema * GetUfeSchema();
      ::user::front_end * GetUfe();

      virtual bool initialize();
      virtual bool finalize();

      virtual void _001CloseAllDocuments(bool bEndSession);
      void add_document_template(::userbase::document_template * ptemplate);
      virtual ::userbase::document* _vmsguserbaseOpenDocumentFile(const char * lpszFileName);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      virtual void _001OnFileNew();
      

   };

   inline application & app_cast(::ax::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }




   CLASS_DECL_ca ::user::front_end_schema * GetUfeSchema(::ax::application * papp);
   CLASS_DECL_ca ::user::front_end * GetUfe(::ax::application * papp);



} // namespace userbase


