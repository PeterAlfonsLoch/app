#pragma once

namespace userbase
{

   class tab_drop_target_window;
   class single_document_template;

   class CLASS_DECL_ca tab_view : 
      virtual public ::userbase::view,
      virtual public ::user::tab,
      virtual public ::user::tab_callback,
      virtual public ::user::get_view
   {
   public:
      tab_view(::ca::application * papp);

      virtual id get_view_id();
      virtual ::user::interaction* get_view_uie();
      virtual ::document * get_view_document();

   protected:
      ::user::create_view *               m_pcreateview;           

   public:
      tab_drop_target_window *       m_pdroptargetwindow;
      ::user::create_view::view_data *    m_pviewdata;
      ::user::create_view::view_data *    m_pviewdataOld;

      void _000OnDraw(::ca::graphics * pdc);

      virtual ::user::create_view * get_create_view();
      virtual void set_create_view(::user::create_view * pcreateview);

      void _001OnDropTab(id id, e_position eposition);
      
      ::user::interaction* _001GetTabWnd(int iTab);

      bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      virtual void _001DropTargetWindowInitialize(::user::tab * pinterface);
      virtual void _001DropTargetWindowRelay(::user::tab * pinterface);
      virtual void _001DropTargetWindowFinalize(::user::tab * pinterface);

      virtual void rotate();

      ::user::create_view::view_data * ensure_tab_by_id(id id);

      virtual void on_show_view();
      virtual void on_show_view(::user::tab * ptab);
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      void _001OnTabClick(int iTab);


      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      DECL_GEN_SIGNAL(_001OnMenuMessage)

      virtual ~tab_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnSetFocus)
   };

   class tab_drop_target_window : 
      virtual public ::user::interaction
   {
   public:
      tab_drop_target_window(::ca::application * papp);
      virtual ~tab_drop_target_window();
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      void _001OnDraw(::ca::graphics * pdc);
      ::user::tab * m_pinterface;
   };

} // namespace userbase