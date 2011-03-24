#pragma once

namespace netshareservercfg
{

class CLASS_DECL_CA2_NETSHARECLIENT document:
   public BaseDocument
{
public:
	document();

	virtual BOOL OnNewDocument();
public:
	virtual ~document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

} // namespace netshareservercfg 