#pragma once

namespace vmssyncheditor
{

class media_view :
   public mediaplay::MediaView
{
   
public:
   media_view(::ca::application * papp);
   virtual void KaraokeGetPosition(imedia::Position & position);

	DECL_GEN_VSIGNAL(data_on_after_change)

      virtual void _001OnInitialUpdate(gen::signal_object * pobj);
	virtual void OnUpdate(view* pSender, LPARAM lHint, base_object* pHint);
	virtual ~media_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECL_GEN_SIGNAL(_001OnTimer)
};

} // namespace vmssyncheditor