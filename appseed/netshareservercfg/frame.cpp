#include "StdAfx.h"
#include "resource.h"

namespace netshareservercfg 
{

frame::frame(::ca::application * papp) :
   ::ca::ca(papp),
   SimpleFrameWindow(papp)
{
   m_iFrameData = 10;
   m_dataid = "MusicalPlayerscreencaptureFrame";

   WfiEnableFullScreen();

   m_dataidWindow = "WindowData";
}

frame::~frame()
{
}

#ifdef _DEBUG
void frame::AssertValid() const
{
	SimpleFrameWindow::AssertValid();
}

void frame::Dump(CDumpContext& dc) const
{
	SimpleFrameWindow::Dump(dc);
}


#endif //_DEBUG




} // namespace netshareservercfg 