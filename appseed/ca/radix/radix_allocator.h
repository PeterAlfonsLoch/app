#pragma once


class trace_process;
class trace_module;
class ::gen::trace::category;


class CTraceSnapshot
{
public:


	struct CModuleInfo
	{


		DWORD_PTR   m_dwModule;
		count       m_nCategories;
		index       m_iFirstCategory;


	};


public:


   raw_array < CModuleInfo >  m_aModules;
   count_array                m_adwCategories;


};



class allocator
{
private:
	

   trace_process *   m_pProcess;
	DWORD             m_dwPageSize;
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

	bool Init(const CHAR *pszFileMappingName, DWORD dwMaxSize);
	bool open(const CHAR *pszFileMappingName);
	void close(bool bForceUnmap = false);
	bool IsValid() const {return m_bValid;}

	trace_process *GetProcess() const {return m_pProcess;}
	trace_module *GetModule(index iModule) const;
//	::gen::trace::category *GetCategory(int iModule, unsigned nCategory) const;
	::gen::trace::category* GetCategory(index iCategory) const;

	/*
	bool Lock(DWORD dwTimeOut);
	void Unlock();
	*/

	bool LoadSettings(const CHAR *pszFileName);
	bool LoadSettings(const WCHAR *pszFileName);
	bool SaveSettings(const CHAR *pszFileName);
	bool SaveSettings(const WCHAR *pszFileName);

	count GetModuleCount() const;
	count GetCategoryCount(index iModule) const;
	int GetCategoryCount(const trace_module& Module) const;

	bool FindModule(const WCHAR *pszModuleName, unsigned *pnModule) const;

	index AddModule(HINSTANCE hInst);
	index AddCategory(index iModule, const CHAR * szCategoryName);

	bool RemoveModule(index iModule);

	void CleanUp();

	void TakeSnapshot();
	void ReleaseSnapshot();




};

