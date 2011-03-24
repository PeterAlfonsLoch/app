#pragma once

namespace netshareservercfg
{

class CLASS_DECL_CA2_NETSHARECLIENT frame : public SimpleFrameWindow
{
	
public:
	frame(::ca::application * papp);
	// DECLARE_DYNCREATE(frame)

public:
	
public:
	virtual ~frame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:


};

} // namespace netshareservercfg