#ifndef ATLDEBUG_SHAREDMEORY_ALLOCATOR_HEADER
#define ATLDEBUG_SHAREDMEORY_ALLOCATOR_HEADER


class trace_process;
class trace_module;
class trace_category;

class CTraceSnapshot
{
public:
   struct CModuleInfo
   {
      DWORD_PTR m_dwModule;
      int m_nCategories;
      int m_iFirstCategory;
   };

public:
   raw_array < CModuleInfo > m_aModules;
   dword_array m_adwCategories;
};

class allocator
{
public:
   allocator() :
      m_dwPageSize(0), 
      m_hMap(NULL),
      m_bValid(false),
      m_pProcess(NULL),
      m_bSnapshot(false)
   {
   }

   ~allocator() 
   {
      close();
   }

   bool Init(const CHAR *pszFileMappingName, DWORD dwMaxSize);
   bool open(const CHAR *pszFileMappingName);
   void close(bool bForceUnmap = false);
   bool IsValid() const {return m_bValid;}

   trace_process *GetProcess() const {return m_pProcess;}
   trace_module *GetModule(int iModule) const;
//   trace_category *GetCategory(int iModule, unsigned nCategory) const;
   trace_category* GetCategory(int iCategory) const;

   /*
   bool Lock(DWORD dwTimeOut);
   void Unlock();
   */

   bool LoadSettings(const CHAR *pszFileName);
   bool LoadSettings(const WCHAR *pszFileName);
   bool SaveSettings(const CHAR *pszFileName);
   bool SaveSettings(const WCHAR *pszFileName);

   int GetModuleCount() const;
   int GetCategoryCount(int iModule) const;
   int GetCategoryCount(const trace_module& Module) const;

   bool FindModule(const WCHAR *pszModuleName, unsigned *pnModule) const;

   int AddModule(HINSTANCE hInst);
   int AddCategory(int iModule, const CHAR *szCategoryName);

   bool RemoveModule(int iModule);

   void CleanUp();

   void TakeSnapshot();
   void ReleaseSnapshot();

   CTraceSnapshot m_snapshot;
   bool m_bSnapshot;

private:
   trace_process *m_pProcess;
   DWORD m_dwPageSize;
   HANDLE m_hMap;
   bool m_bValid;
   BYTE *m_pBufferStart;
};

#endif // ATLDEBUG_SHAREDMEORY_ALLOCATOR_HEADER
