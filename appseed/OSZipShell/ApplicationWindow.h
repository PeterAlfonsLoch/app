#pragma once


// ApplicationWindow

class ApplicationWindow : public CWnd
{
	DECLARE_DYNAMIC(ApplicationWindow)

public:
	ApplicationWindow();
	virtual ~ApplicationWindow();

   bool Create();

protected:
	DECLARE_MESSAGE_MAP()
};


