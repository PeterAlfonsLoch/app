#pragma once


class CChildFrame : public CMDIChildWnd
{
public:
   CChildFrame(::ca::application * papp);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECL_GEN_SIGNAL(_001OnCreate)

      
};

