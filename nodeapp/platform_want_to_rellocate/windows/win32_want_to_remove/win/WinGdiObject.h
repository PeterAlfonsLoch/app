// WinGdiObject.h: interface for the WinGdiObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINGDIOBJECT_H__525D9E27_9BDE_4EB9_BF97_E29CE72C1EF3__INCLUDED_)
#define AFX_WINGDIOBJECT_H__525D9E27_9BDE_4EB9_BF97_E29CE72C1EF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// WinGdiObject abstract class for ::ca::graphics_sp SelectObject

class WinGdiObject : public base_object
{
	// // DECLARE_DYNCREATE(WinGdiObject)
public:

// Attributes
	HGDIOBJ m_hObject;                  // must be first data member
	operator HGDIOBJ() const;
	HGDIOBJ get_os_data() const;

	static WinGdiObject* PASCAL from_handle(HGDIOBJ hObject);
	static void PASCAL DeleteTempMap();
	BOOL Attach(HGDIOBJ hObject);
	HGDIOBJ Detach();

// Constructors
	WinGdiObject(); // must create a derived class object
	BOOL DeleteObject();

// Operations
	int GetObject(int nCount, LPVOID lpObject) const;
	UINT GetObjectType() const;
	BOOL CreateStockObject(int nIndex);
	BOOL UnrealizeObject();
	BOOL operator==(const WinGdiObject& obj) const;
	BOOL operator!=(const WinGdiObject& obj) const;

// ementation
public:
	virtual ~WinGdiObject();
#ifdef _DEBUG
	virtual void dump(dump_context & dumpcontext) const;
	virtual void assert_valid() const;
#endif
};

#endif // !defined(AFX_WINGDIOBJECT_H__525D9E27_9BDE_4EB9_BF97_E29CE72C1EF3__INCLUDED_)
