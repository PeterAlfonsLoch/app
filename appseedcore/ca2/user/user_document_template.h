#pragma once


#include "user_document_request_interface.h"


class CLASS_DECL_ca document_template : 
   virtual public command_target,
   virtual public ::user::document_request_interface
{
public:


   gen::property_set       m_set;


protected:


   document_template(::ca::application * papp, const char * pszMatter, ::ca::type_info pDocClass,
      ::ca::type_info pFrameClass, ::ca::type_info pViewClass);


public:

   virtual void load_template();

   virtual count get_document_count() const = 0;
   virtual document * get_document(index index = 0) const = 0;

   virtual void add_document(document * pDoc);      // must override
   virtual void remove_document(document * pDoc);   // must override

   enum DocStringIndex
   {
      windowTitle,        // default ::ca::window title
      docName,            // ::fontopus::user visible name for default document
      fileNewName,        // ::fontopus::user visible name for FileNew
      // for file based documents:
      filterName,         // ::fontopus::user visible name for FileOpen
      filterExt,          // ::fontopus::user visible extension for FileOpen
      // for file based documents with Shell open support:
      regFileTypeId,      // REGEDIT visible registered file type identifier
      regFileTypeName,    // Shell visible registered file type name
   };
   virtual BOOL GetDocString(string & rString,
      enum DocStringIndex index) const; // get one of the info strings
   //frame_window* CreateOleFrame(::ca::window* pParentWnd, document * pDoc,
   //   BOOL bCreateView);

   void update_all_views(::view * pviewSender, LPARAM lhint, ::radix::object * puh);

// Overridables
public:
   enum Confidence
   {
      noAttempt,
      maybeAttemptForeign,
      maybeAttemptNative,
      yesAttemptForeign,
      yesAttemptNative,
      yesAlreadyOpen
   };
   virtual Confidence MatchDocType(const char * lpszPathName, document *& rpDocMatch);
   virtual document * create_new_document();
   virtual frame_window* create_new_frame(document * pDoc, frame_window* pOther, ::user::interaction * pwndParent = NULL, ::user::interaction * puiAlloc = NULL);
   virtual void InitialUpdateFrame(frame_window* pFrame, document * pDoc, BOOL bMakeVisible = TRUE);
   virtual BOOL save_all_modified();     // for all documents
   virtual void close_all_documents(BOOL bEndSession);
   virtual void request(var & varFile, var & varRequest) = 0;
               // open named file
               // if lpszPathName == NULL => create new file with this type
   virtual void set_default_title(document * pdocument) = 0;

// Implementation
public:
   BOOL m_bAutoDelete;
   virtual ~document_template() = 0;

   // back pointer to OLE or other server (NULL if none or disabled)
   ::radix::object* m_pAttachedFactory;

   // menu & accelerator resources for in-place container
   //HMENU m_hMenuInPlace;
   //HACCEL m_hAccelInPlace;

   // menu & accelerator resource for server editing embedding
   //HMENU m_hMenuEmbedding;
   //HACCEL m_hAccelEmbedding;

   // menu & accelerator resource for server editing in-place
   //HMENU m_hMenuInPlaceServer;
   //HACCEL m_hAccelInPlaceServer;

#ifdef _DEBUG
   virtual void dump(dump_context&) const;
   virtual void assert_valid() const;
#endif
   virtual void on_idle();             // for all documents
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
      

protected:
   string m_strMatter;                 // IDR_ for frame/menu/accel as well
   //string m_strServerMatter;           // IDR_ for OLE inplace frame/menu/accel
   //UINT m_nIDEmbeddingResource;        // IDR_ for OLE open frame/menu/accel
   //UINT m_nIDContainerResource;        // IDR_ for container frame/menu/accel

   ::ca::type_info m_typeinfoDocument;         // class for creating new documents
   ::ca::type_info m_typeinfoFrame;       // class for creating new frames
   ::ca::type_info m_typeinfoView;        // class for creating new views
   //::ca::type_info m_pOleFrameClass;    // class for creating in-place frame
   //::ca::type_info m_pOleViewClass;     // class for creating in-place ::view

   string m_strDocStrings;    // '\n' separated names
      // The document names sub-strings are represented as _one_ string:
      // windowTitle\ndocName\n ... (see DocStringIndex enum)
};
