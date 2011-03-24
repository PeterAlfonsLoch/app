// WinEx1Factory.cpp: implementation of the WinEx1Factory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinEx1Factory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WinEx1Factory::WinEx1Factory()
{

}

WinEx1Factory::~WinEx1Factory()
{

}

Ex1Impl * WinEx1Factory::New(Ex1Interface * pinterface)
{
   const type_info & ti = typeid(pinterface);

   if(ti == typeid(File))
      return
}


AppInterfaceImpl * WinEx1Factory::NewAppInterface()
{
   return new WinAppInterfaceImpl;
}

::FileImpl * WinEx1Factory::NewFile()
{
   return WinFile;
}

::FileImpl * WinEx1Factory::NewFile(int hFile)
{
   return WinFile(hFile);
}

::FileImpl * WinEx1Factory::NewFile(LPCWSTR lpszFileName, UINT nOpenFlags)
{
   return WinFile(lpszFileName, nOpenFlags);
}

::FileExceptionImpl * WinEx1Factory::NewFileException(int cause, LONG lOsError, LPCWSTR pstrFileName)
{ 
   return WinFileException(cause, lOsError, pstrErrorName);
}

::Ex1ResourceImpl * WinEx1Factory::NewEx1Resource()
{
   return newWinRessource;
}
