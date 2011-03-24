#pragma once

class CBaseMDIChildWnd : public SimpleMDIChildWindow
{
public:
   CBaseMDIChildWnd(::ca::application * papp);

public:
    virtual CMDIFrameWnd* GetMDIFrame();
public:

protected:
	virtual ~CBaseMDIChildWnd();

	DECLARE_MESSAGE_MAP()
};
