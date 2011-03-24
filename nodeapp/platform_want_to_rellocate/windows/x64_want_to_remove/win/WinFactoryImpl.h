// WinFactoryImpl.h: interface for the WinFactoryImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINFACTORYIMPL_H__9E87ABB2_D193_4C6E_A303_0C23CD25627A__INCLUDED_)
#define AFX_WINFACTORYIMPL_H__9E87ABB2_D193_4C6E_A303_0C23CD25627A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLASS_DECL_VMSWIN WinFactoryImpl :
   public Ex1FactoryImpl
{
public:
	WinFactoryImpl();
	virtual ~WinFactoryImpl();

   virtual Ex1Impl * New(::ca::type_info ti);


};

#endif // !defined(AFX_WINFACTORYIMPL_H__9E87ABB2_D193_4C6E_A303_0C23CD25627A__INCLUDED_)
