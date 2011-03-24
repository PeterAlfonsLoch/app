
#ifndef _Song_____
#define _Song_____

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DB_SONGS_ORDINAL 2
#define DB_SONGS_CODE 3
#define DB_SONGS_COUNTRY 4
#define DB_SONGS_NAME 5
#define DB_SONGS_COMPOSER 6
#define DB_SONGS_LYRICIST 7
#define DB_SONGS_ARRANGER 8
#define DB_SONGS_PERFORMER 9
#define DB_SONGS_PROGRAMMER 10
#define DB_SONGS_KEYWORD 11
#define DB_SONGS_PATH 12

class CKarInfo;
class CTune1000Info;
class CDBLongSet;

class CFolderSongBase
{
public:
	void Destruct();
	void Construct();
	CFolderSongBase();
	virtual ~CFolderSongBase();
	CFolderSongBase & operator =(CFolderSongBase *pSrc);

	int		m_iKey;
	int		m_iParentKey;
	BSTR	m_bstrName;

};

class CFolderSong  : public CFolderSongBase
{
public:
	string GetName();
	void Normalize();
	ULONG	m_sKey;
   	ULONG	m_sParentKey;
	ULONG	m_sName;
	ULONG	m_lName;
		

   int m_iKey;
   int m_iParentKey;
   string m_bstrName;
};

class CFolderSongsSet :
	public DBSetInterface
{
private:
//	CComPtr<IRowsetIndex> m_spRowsetIndex;
	BOOL					m_bIndexedOrdinal;
	BOOL					m_bIndexedKey;
	BOOL					m_bIndexedPath;
	string					m_strWhereClause;
	string					m_strFromClause;

public:
	CCriticalSection m_cs;

	
public:
	string GetWhereClause();
	bool SetWhereClause(int iMask, LPCTSTR lpcszText);
	bool LoadColumnSortArray(CDBLongSet * pLongsSet, LPCSTR lpcszBaseKey);
	bool SaveColumnSortArray(CDBLongSet *pLongsSet, LPCSTR lpcszBaseKey);
	HRESULT GetKeys(CDWordArray * dwaKeys);
    bool SetWhereClause(LPCTSTR lpcszSql);
	bool SetFromClause(LPCTSTR lpcszSql);
	CFolderSongsSet(CDataCentral * pdatacentral);
	HRESULT Execute(IRowset** ppRowset, DBPARAMS* pParams, DBPROPSET *pPropSet, LONG* pRowsAffected);
	void SetupOptionalRowsetInterfaces();
//	static const IID& GetIID()
//	{
//		return IID_IRowsetIndex;
//	}
//	IRowsetIndex* GetInterface() const
//	{
//		return m_spRowsetIndex;
//	}
//	IRowsetIndex** GetInterfacePtr()
//	{
//		return &m_spRowsetIndex;
//	}

	HRESULT RemoveAll();
// Attributes
	CDWordArray m_SortingColumns;
	CDWordArray m_ColumnsSorting;


// Operations	
	int GetRecordCount();
	BOOL GetNextFile(LPSTR *pStr);
	void Sort(int ColumnIndex);
	void Sort();
	
	

/*	BOOL FindClasse(int Classe)
	{
		if(FAILED(MoveFirst()))
			return FALSE;
		while(TRUE)
		{
			if(FAILED(GetData()))
				return FALSE;
			if(Classe == m_Classe)
				return TRUE;
			if(FAILED(MoveNext()))
				return FALSE;
		}
	}

	static HRESULT GetNewClasse(CDataSource db, int Pedido, int *newClasse)
	{
		CClassesPecasClasseSet set;
		string strSQL;
		strSQL.Format("SELECT TOP 1 Classe FROM ClassesPecas WHERE ClassesPecas.Pedido = %d ORDER BY ClassesPecas.Classe DESC;", Pedido);
		HRESULT hr = set.Open(db, strSQL);
		if (FAILED(hr))
			return hr;
		if(FAILED(hr = set.MoveFirst()))
			return hr;
		*newClasse =  set.m_Classe + 1;
		return S_OK;
	} */

};

#endif