#pragma once


class CMidiTrackSelectFrame : public CMDIChildWnd
{
public:
   CMidiTrackSelectFrame(::ca::application * papp);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CMidiTrackSelectFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECL_GEN_SIGNAL(_001OnCreate)
};

