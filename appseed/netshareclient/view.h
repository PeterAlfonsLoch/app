#pragma once

namespace netshareclient
{
   class socket;

   class CLASS_DECL_CA2_NETSHARECLIENT view : 
      public ::userbase::view
   {
   public:

      bool                       m_bHover;
      netshareclient::thread *   m_pthread;
      netshareclient::area *     m_parea;
      string                     m_strServer;


      view(::ca::application * papp);
	   virtual ~view();

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);

      virtual bool netshare(const char * pszServer);

      int run();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual void _001OnTabClick(int iTab);

      DECL_GEN_SIGNAL(_001OnInitialUpdate)
	   DECL_GEN_SIGNAL(_001OnDestroy)
	   DECL_GEN_SIGNAL(_001OnSize)
	   DECL_GEN_SIGNAL(_001OnPaint)
	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnContextMenu)
	   DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnUser1024) 
      
   };

} // namespace netshareclient
