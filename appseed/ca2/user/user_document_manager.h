#pragma once


class CLASS_DECL_ca2 document_manager : 
   virtual public ::user::document_request_interface
{
public:


   comparable_array < document_template * >  m_templateptra;


   static const char _afxShellOpenFmt[];
   static const char _afxShellPrintFmt[];
   static const char _afxShellPrintToFmt[];
   static const char _afxDefaultIconFmt[];
   static const char _afxShellNewFmt[];

   #define DEFAULT_ICON_INDEX 0

   static  const char _afxIconIndexFmt[];
   static  const char _afxCommand[];
   static  const char _afxOpenArg[];
   static  const char _afxPrintArg[];
   static  const char _afxPrintToArg[];
   static  const char _afxDDEArg[];

   static  const char _afxDDEExec[];
   static  const char _afxDDEOpen[];

   static const char _afxDDEPrint[];
   static const char _afxDDEPrintTo[];

   static const char _afxShellNewValueName[];
   static const char _afxShellNewValue[];


   document_manager();
   virtual ~document_manager();


#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif


   virtual void add_document_template(document_template * ptemplate);
   virtual count get_template_count() const;
   virtual document_template * get_template(index index) const;
   virtual void RegisterShellFileTypes(BOOL bCompat);
   void UnregisterShellFileTypes();
   virtual void request(::ca::create_context * pcreatecontext); // open named file
   virtual BOOL save_all_modified(); // save before exit
   virtual void close_all_documents(BOOL bEndSession); // close documents before exiting
   virtual int get_open_document_count();

   virtual BOOL do_prompt_file_name(string & fileName, UINT nIDSTitle,
         DWORD lFlags, BOOL bOpenFileDialog, document_template * ptemplate);

   virtual BOOL OnDDECommand(LPTSTR lpszCommand);
   virtual void _001OnFileNew();
   virtual void on_file_open();

   int get_document_count(); // helper to count number of total documents



};
