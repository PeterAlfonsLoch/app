#pragma once

/////////////////////////////////////////////////////////////////////////////
// CHtmlEditView
#define AFX_INVALID_DHTML_CMD_ID 0xFFFFFFFF
#define AFX_UI_ELEMTYPE_NORMAL	0
#define AFX_UI_ELEMTYPE_CHECBOX	1
#define AFX_UI_ELEMTYPE_RADIO	2


#define DECLARE_DHTMLEDITING_CMDMAP(className) \
public: \
	UINT GetDHtmlCommandMapping(UINT nIDWindowsCommand, BOOL&, UINT&); \
	BOOL ExecHandler(UINT nCmdID); \
	typedef void  (className##::*PFN_##className##_CMDHDLR)(UINT); \
	struct className##dhtml_cmd_mapping \
	{ \
		UINT windowsCommand; \
		UINT dhtmlCommand; \
		UINT nElementType; \
		PFN_##className##_CMDHDLR pfn; \
	}; \
	static className##dhtml_cmd_mapping m_commands[];\

#define DHTMLEDITING_CMD_ENTRY(cmdID, dhtmlcmdID)\
{cmdID, dhtmlcmdID, AFX_UI_ELEMTYPE_NORMAL, NULL}, 

#define DHTMLEDITING_CMD_ENTRY_FUNC(cmdID, dhtmlcmdID, member_func_name)\
{cmdID, dhtmlcmdID, AFX_UI_ELEMTYPE_NORMAL, member_func_name},

#define DHTMLEDITING_CMD_ENTRY_TYPE(cmdID, dhtmlcmdID, elemType)\
{cmdID, dhtmlcmdID, elemType, NULL}, 

#define DHTMLEDITING_CMD_ENTRY_FUNC_TYPE(cmdID, dhtmlcmdID, member_func_name, elemType)\
{cmdID, dhtmlcmdID, elemType, member_func_name},

#define BEGIN_DHTMLEDITING_CMDMAP(className) \
PTM_WARNING_DISABLE \
BOOL className##::ExecHandler(UINT nWindowsCommand)\
{\
	const className##dhtml_cmd_mapping *pMapping = className##::m_commands;\
	while (pMapping->dhtmlCommand != 0)\
	 {\
	 if (nWindowsCommand == pMapping->windowsCommand)\
	 {\
		(this->*pMapping->pfn)(pMapping->dhtmlCommand);\
		return TRUE;\
	 }\
	 pMapping++;\
	 }\
	return FALSE;\
}\
UINT className##::GetDHtmlCommandMapping(UINT nIDWindowsCommand, BOOL& bHasExecFunc, UINT& uiElemType)\
{ \
	const className##dhtml_cmd_mapping *pMapping = className##::m_commands;\
	 while (pMapping->dhtmlCommand != 0)\
	 {\
	 if (pMapping->windowsCommand == nIDWindowsCommand)\
	 {\
		 bHasExecFunc = pMapping->pfn != NULL ? TRUE : FALSE;\
		 uiElemType = pMapping->nElementType;\
		 return pMapping->dhtmlCommand;\
	 }\
	 pMapping++;\
	 }\
	return AFX_INVALID_DHTML_CMD_ID;\
}\
className##::className##dhtml_cmd_mapping className##::m_commands[] = {

#define END_DHTMLEDITING_CMDMAP()\
		{0, 0, 0, NULL} \
	}; \
	PTM_WARNING_RESTORE



class CLASS_DECL_CAFX CHtmlEditView :
	public CHtmlView,
	public CHtmlEditCtrlBase<CHtmlEditView>
{
public:
	CHtmlEditView();

	// Retrieve the IHTMLDocument2 interface associated with the
	// document loaded in the contained WebBrowser control.
	BOOL GetDHtmlDocument(IHTMLDocument2 **ppDocument) const;

	// Create a new window object. This function will also call the
	// contained WebBrowser's Navigate method to load a default document.
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, const RECT& rect, base_wnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL);

	// Retrieve the name of the default document for this view.
	virtual LPCTSTR GetStartDocument();

// Implementation
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo);
	virtual UINT GetDHtmlCommandMapping(UINT nIDWindowsCommand, BOOL& bHasExecFunc, UINT& uiElemType);
	virtual BOOL ExecHandler(UINT nCmdID);
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	void OnPaint();
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CHtmlEditView)
	virtual ~CHtmlEditView();
};

