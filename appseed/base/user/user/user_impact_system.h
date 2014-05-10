#pragma once


namespace user
{


   class CLASS_DECL_BASE impact_system :
      virtual public ::object,
      virtual public command_target,
      virtual public ::user::server
   {
   public:


      enum DocStringIndex
      {
         
         windowTitle,        // default window title
         docName,            // ::fontopus::user visible name for default ::user::object
         fileNewName,        // ::fontopus::user visible name for FileNew
         // for file based documents:
         filterName,         // ::fontopus::user visible name for FileOpen
         filterExt,          // ::fontopus::user visible extension for FileOpen
         // for file based documents with Shell open support:
         regFileTypeId,      // REGEDIT visible registered file type identifier
         regFileTypeName    // Shell visible registered file type name
            
      };

      
      enum Confidence
      {
         
         noAttempt,
         maybeAttemptForeign,
         maybeAttemptNative,
         yesAttemptForeign,
         yesAttemptNative,
         yesAlreadyOpen
            
      };
      

      class on_open_document
      {
      public:


         sp(impact_system)                 m_pschema;
         sp(::user::object)        m_pdocument;
         var                                 m_varFile;



      };




      bool                    m_bQueueDocumentOpening;
      property_set       m_set;
      bool                    m_bAutoDelete;
      // back pointer to OLE or other server (NULL if none or disabled)
      object *       m_pAttachedFactory;

      // menu & accelerator resources for in-place container
      //HMENU                 m_hMenuInPlace;
      //HACCEL                m_hAccelInPlace;

      // menu & accelerator resource for server editing embedding
      //HMENU                 m_hMenuEmbedding;
      //HACCEL                m_hAccelEmbedding;

      // menu & accelerator resource for server editing in-place
      //HMENU                 m_hMenuInPlaceServer;
      //HACCEL                m_hAccelInPlaceServer;

      string                  m_strMatter;                 // IDR_ for frame/menu/accel as well
      //string                m_strServerMatter;           // IDR_ for OLE inplace frame/menu/accel
      //UINT                  m_nIDEmbeddingResource;        // IDR_ for OLE open frame/menu/accel
      //UINT                  m_nIDContainerResource;        // IDR_ for container frame/menu/accel

      sp(type)         m_typeinfoDocument;         // class for creating new documents
      sp(type)         m_typeinfoFrame;       // class for creating new frames
      sp(type)         m_typeinfoView;        // class for creating new views
      //sp(type)       m_pOleFrameClass;    // class for creating in-place frame
      //sp(type)       m_pOleViewClass;     // class for creating in-place ::user::impact

      string                  m_strDocStrings;    // '\n' separated names
      // The ::user::object names sub-strings are represented as _one_ string:
      // windowTitle\ndocName\n ... (see DocStringIndex enum)

      impact_system(sp(::base::application) papp, const char * pszMatter, sp(type) pDocClass, sp(type) pFrameClass, sp(type) pViewClass);

      virtual void load_template();

      virtual ::count get_document_count() const = 0;
      virtual sp(::user::object) get_document(index index = 0) const = 0;

      virtual void add_document(sp(::user::object) pDoc);      // must override
      virtual void remove_document(sp(::user::object) pDoc);   // must override

      virtual bool GetDocString(string & rString, enum DocStringIndex index) const; // get one of the info strings
      //sp(::user::frame_window) CreateOleFrame(::window_sp pParentWnd, sp(::user::object) pDoc,
      //   bool bCreateView);

      void update_all_views(sp(::user::impact) pviewSender, LPARAM lhint, ::object * puh);

      virtual Confidence MatchDocType(const char * lpszPathName, sp(::user::object)& rpDocMatch);
      virtual sp(::user::object) create_new_document(sp(::create_context) pcreatecontext);
      virtual sp(::user::frame_window) create_new_frame(sp(::user::object) pDoc, sp(::user::frame_window) pOther, sp(::create_context) pcreatecontext);
      virtual void InitialUpdateFrame(sp(::user::frame_window) pFrame, sp(::user::object) pDoc, bool bMakeVisible = TRUE);
      virtual bool save_all_modified();     // for all documents
      virtual void close_all_documents(bool bEndSession);
      virtual void request_create(sp(::create_context) pcreatecontext) = 0;
      // open named file
      // if lpszPathName == NULL => create new file with this type
      virtual void set_default_title(sp(::user::object) pdocument) = 0;

      virtual ~impact_system() = 0;


      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;

      virtual void on_idle();             // for all documents
      virtual bool _001OnCmdMsg(base_cmd_msg * pcmdmsg);


      bool on_open_document(sp(::user::object) pdoc, var varFile);

      bool do_open_document(sp(::user::object) pdoc, var varFile);

      static UINT s_on_open_document(LPVOID lpvoid);

      virtual void reload_template();

   };




} // namespace user







