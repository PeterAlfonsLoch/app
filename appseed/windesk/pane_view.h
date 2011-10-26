#pragma once

#include "pane_view_update_hint.h"

namespace windesk
{

   class CLASS_DECL_CA2_WINDESK pane_view : 
      public ::userex::pane_tab_view,
      public FileManagerCallbackInterface,
      public windesk::form_callback
   {
   public:
      form_view *                               m_pformOptions;
      visual::dib_sp                               m_dibBk;
      int                                       m_iNewArea;
      int                                       m_iArea;
      int                                       m_iDisplay;
      filemanager::SimpleFilePropertiesForm *   m_ppropform;
      ::fs::item_array                      m_itema;

	   pane_view(::ca::application * papp);
	   virtual ~pane_view();

      void rotate();
      
      void on_create_view(::user::view_creator_data * pcreatordata);
      void on_show_view();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      void check_3click_dir(const char * psz);
      void check_menu_dir(const char * psz);
      void check_desktop_dir(const char * psz);

      void _001InitializeFormPreData(::user::form * pform);
      bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      
   /*	virtual void OnFileManagerOpenContextMenuFolder(
         ::filemanager::data * pdata, 
         FileManagerItem & item);*/
	   virtual void OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::fs::item_array & itema);
	   virtual void OnFileManagerOpenContextMenu(::filemanager::data * pdata);

      void _001OnDraw(::ca::graphics * pdc);

      virtual void set_display(int iDisplay);

	   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnMenuMessage)
	   DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnRButtonUp)
      DECL_GEN_SIGNAL(_001OnProperties)

   };


} // namespace windesk

