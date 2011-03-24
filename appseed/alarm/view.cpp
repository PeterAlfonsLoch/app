#include "StdAfx.h"


namespace alarm
{

   
   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(user::win::message::dispatch * pinterface)
   {
      userbase::view::_001InstallMessageHandling(this);
   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context& dc) const
   {
	   ::userbase::view::dump(dc);
   }
   #endif //_DEBUG


   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
/*      cs.lpszClass = AfxRegisterWndClass(
		   CS_DBLCLKS |
		   CS_OWNDC,
		   0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;*/
	   return ::userbase::view::PreCreateWindow(cs);
   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
   }

   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      pdc->SetBkMode(TRANSPARENT);
   }

} // namespace alarm