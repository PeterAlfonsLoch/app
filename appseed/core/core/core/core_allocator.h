#pragma once


class trace_process;
class trace_module;
class ::aura::trace::category;


class CTraceSnapshot
{
public:


	struct CModuleInfo
	{


		uint_ptr   m_dwModule;
		::count m_nCategories;
		index       m_iFirstCategory;


	};


public:


   array < CModuleInfo >  m_aModules;
   count_array                m_adwCategories;


};



class allocator
{
private:
	

   trace_process *   m_pProcess;
	uint32_t             m_dwPageSize;
	HANDLE            m_hMap;
	bool              m_bValid;
	BYTE *            m_pBufferStart;


public:

	
   CTraceSnapshot    m_snapshot;
	bool              m_bSnapshot;


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

	bool Init(const CHAR *pszFileMappingName, uint32_t dwMaxSize);
	bool open(const CHAR *pszFileMappingName);
	void close(bool bForceUnmap = false);
	bool IsValid() const {return m_bValid;}

	trace_process *GetProcess() const {return m_pProcess;}
	trace_module *GetModule(index iModule) const;
//	::aura::trace::category *GetCategory(int32_t iModule, uint32_t nCategory) const;
	::aura::trace::category* GetCategory(index iCategory) const;

	/*
	bool Lock(uint32_t dwTimeOut);
	void Unlock();
	*/

	bool LoadSettings(const CHAR *pszFileName);
	bool LoadSettings(const WCHAR *pszFileName);
	bool SaveSettings(const CHAR *pszFileName);
	bool SaveSettings(const WCHAR *pszFileName);

	::count GetModuleCount() const;
	::count GetCategoryCount(index iModule) const;
	int32_t GetCategoryCount(const trace_module& Module) const;

	bool FindModule(const WCHAR *pszModuleName, uint32_t *pnModule) const;

	index AddModule(HINSTANCE hInst);
	index AddCategory(index iModule, const CHAR * szCategoryName);

	bool RemoveModule(index iModule);

	void CleanUp();

	void TakeSnapshot();
	void ReleaseSnapshot();




};

