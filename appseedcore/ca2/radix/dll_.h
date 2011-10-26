#pragma once

#ifdef WINDOWS

// AFX_EXTENSION_MODULE - special struct used during DLL initialization

struct CLASS_DECL_ca AFX_EXTENSION_MODULE
{
   BOOL bInitialized;
   HMODULE hModule;
   HMODULE hResource;
   ::ca::type_info pFirstSharedClass;
};

/////////////////////////////////////////////////////////////////////////////
// CDynLinkLibrary - for implementation of ca2 API Extension DLLs

class COleObjectFactory;

class CLASS_DECL_ca CDynLinkLibrary : public command_target
{

public:

// Constructor
   explicit CDynLinkLibrary(AFX_EXTENSION_MODULE& state, BOOL bSystem = FALSE);
   CDynLinkLibrary(HINSTANCE hModule, HINSTANCE hResource);

// Attributes
   HMODULE m_hModule;
   HMODULE m_hResource;                // for shared resources
   BOOL m_bSystem;                     // TRUE only for ca2 API DLLs

// Implementation
public:
   CDynLinkLibrary* m_pNextDLL;        // simple singly linked list
   virtual ~CDynLinkLibrary();

#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif //_DEBUG
};

// call in every DLL_PROCESS_ATTACH
CLASS_DECL_ca BOOL AfxInitExtensionModule(AFX_EXTENSION_MODULE&, HMODULE hMod);
// call on every DLL_PROCESS_DETACH
CLASS_DECL_ca void AfxTermExtensionModule(AFX_EXTENSION_MODULE&, BOOL bAll = FALSE);

// special function(s) for stand-alone DLLs (and controls)
CLASS_DECL_ca void AfxCoreInitModule();
#define AfxOleInitModule()
#define AfxNetInitModule()
#define AfxDbInitModule()


// special functions for loading and freeing ca2 API extension DLLs
// (necessary if your cast is multithreaded and loads extension
//  DLLs dynamically)
HINSTANCE AfxLoadLibrary(const char * lpszModuleName);
HINSTANCE AfxLoadLibraryEx( const char * lpFileName,  HANDLE hFile,  DWORD dwFlags);
BOOL AfxFreeLibrary(HINSTANCE hInstLib);


#endif
