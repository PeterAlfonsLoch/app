#pragma once


class CXView : 
   public mediaplay::MediaView
{
protected:
   CXView(::ca::application * papp);
   virtual ~CXView();

	virtual void _001OnDraw(CDC* pDC); 
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

