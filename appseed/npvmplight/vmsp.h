// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IXfplayer wrapper class

class IXfplayer : public COleDispatchDriver
{
public:
	IXfplayer() {}		// Calls COleDispatchDriver default constructor
	IXfplayer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IXfplayer(const IXfplayer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL OpenFile(LPCTSTR bstrFilePath, BOOL bMakeVisible);
};
