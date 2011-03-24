// WinEx1Factory.h: interface for the WinEx1Factory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINEX1FACTORY_H__B974B9C0_14DB_466D_BD58_58BD765790CD__INCLUDED_)
#define AFX_WINEX1FACTORY_H__B974B9C0_14DB_466D_BD58_58BD765790CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsex1FactoryImpl.h"

class WinEx1Factory :
   public _vmsex1::FactoryImpl 
{
public:
	WinEx1Factory();
	virtual ~WinEx1Factory();

   virtual _vmsex1::AppInterfaceImpl * NewAppInterface();
   virtual ::FileImpl * NewFile();
   virtual ::FileImpl * NewFile(int hFile);
   virtual ::FileImpl * NewFile(LPCWSTR lpszFileName, UINT nOpenFlags);
   virtual ::FileExceptionImpl * NewFileException(int cause, LONG lOsError,	LPCWSTR pstrFileName = NULL);
   virtual ::Ex1ResourceImpl * NewEx1Resource();


};

#endif // !defined(AFX_WINEX1FACTORY_H__B974B9C0_14DB_466D_BD58_58BD765790CD__INCLUDED_)
