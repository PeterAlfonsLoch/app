#pragma once

namespace eluce
{

   class socket;

   class CLASS_DECL_CA2_CUBE view : public ::userbase::view
   {
   public:
      view(::ca::application * papp);
      virtual ~view();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001OnDraw(::ca::graphics * pdc);

      visual::dib_sp      m_spdib;
      string m_strServer;

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      DECL_GEN_SIGNAL(_001OnInitialUpdate)
         virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnEraseBkgnd)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)

      virtual void _001OnTabClick(int iTab);
      
   };

} // namespace eluce
