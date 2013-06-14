#pragma once


#include "user_document_request_interface.h"


namespace user
{


   class CLASS_DECL_ca2 document_template :
      virtual public command_target,
      virtual public ::user::document_request_interface,
      virtual public ::user::document_template_interface
   {
   public:


      class on_open_document
      {
      public:


         sp(document_template)                 m_ptemplate;
         sp(::user::document_interface)        m_pdocument;
         var                                 m_varFile;



      };


      enum DocStringIndex
      {
         windowTitle,        // default ::ca2::window title
         docName,            // ::fontopus::user visible name for default ::user::document_interface
         fileNewName,        // ::fontopus::user visible name for FileNew
         // for file based documents:
         filterName,         // ::fontopus::user visible name for FileOpen
         filterExt,          // ::fontopus::user visible extension for FileOpen
         // for file based documents with Shell open support:
         regFileTypeId,      // REGEDIT visible registered file type identifier
         regFileTypeName,    // Shell visible registered file type name
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


      bool                    m_bQueueDocumentOpening;
      ::ca2::property_set       m_set;
      bool                    m_bAutoDelete;
      // back pointer to OLE or other server (NULL if none or disabled)
      ::ca2::object *       m_pAttachedFactory;

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

      sp(::ca2::type_info)         m_typeinfoDocument;         // class for creating new documents
      sp(::ca2::type_info)         m_typeinfoFrame;       // class for creating new frames
      sp(::ca2::type_info)         m_typeinfoView;        // class for creating new views
      //sp(::ca2::type_info)       m_pOleFrameClass;    // class for creating in-place frame
      //sp(::ca2::type_info)       m_pOleViewClass;     // class for creating in-place ::user::view

      string                  m_strDocStrings;    // '\n' separated names
      // The ::user::document_interface names sub-strings are represented as _one_ string:
      // windowTitle\ndocName\n ... (see DocStringIndex enum)

      document_template(sp(::ca2::application) papp, const char * pszMatter, sp(::ca2::type_info) pDocClass, sp(::ca2::type_info) pFrameClass, sp(::ca2::type_info) pViewClass);

      virtual void load_template();

      virtual ::count get_document_count() const = 0;
      virtual sp(::user::document_interface) get_document(index index = 0) const = 0;

      virtual void add_document(sp(::user::document_interface) pDoc);      // must override
      virtual void remove_document(sp(::user::document_interface) pDoc);   // must override

      virtual bool GetDocString(string & rString, enum DocStringIndex index) const; // get one of the info strings
      //sp(::user::frame_window) CreateOleFrame(sp(::ca2::window) pParentWnd, sp(::user::document_interface) pDoc,
      //   bool bCreateView);

      void update_all_views(sp(::user::view) pviewSender, LPARAM lhint, ::ca2::object * puh);

      virtual Confidence MatchDocType(const char * lpszPathName, sp(::user::document_interface)& rpDocMatch);
      virtual sp(::user::document_interface) create_new_document();
      virtual sp(::user::frame_window) create_new_frame(sp(::user::document_interface) pDoc, sp(::user::frame_window) pOther, sp(::ca2::create_context) pcreatecontext);
      virtual void InitialUpdateFrame(sp(::user::frame_window) pFrame, sp(::user::document_interface) pDoc, bool bMakeVisible = TRUE);
      virtual bool save_all_modified();     // for all documents
      virtual void close_all_documents(bool bEndSession);
      virtual void request_create(sp(::ca2::create_context) pcreatecontext) = 0;
      // open named file
      // if lpszPathName == NULL => create new file with this type
      virtual void set_default_title(sp(::user::document_interface) pdocument) = 0;

      virtual ~document_template() = 0;


      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;

      virtual void on_idle();             // for all documents
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      bool on_open_document(sp(::user::document_interface) pdoc, var varFile);

      bool do_open_document(sp(::user::document_interface) pdoc, var varFile);

      static UINT s_on_open_document(LPVOID lpvoid);

      virtual void reload_template();

   };




} // namespace user







