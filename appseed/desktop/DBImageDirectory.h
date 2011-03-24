
#ifndef _IMAGEDIRECTORY_____
#define _IMAGEDIRECTORY_____

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CWStrArray;

class DBImageDirectorySet :
   public DBStringArraySet
{
public:
   enum EUserMessage
   {
      UserMessageOnImageDirectoryChange = 454647,
   };
	DBImageDirectorySet();
	HRESULT Add(const String &str);

	CCriticalSection	m_cs;
	String				m_strRegistrySection;

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
		String strSQL;
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