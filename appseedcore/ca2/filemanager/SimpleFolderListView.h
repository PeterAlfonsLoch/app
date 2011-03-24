#pragma once

#include "SimpleFolderListInterface.h"


namespace filemanager
{

class CLASS_DECL_ca SimpleFolderListView :
   virtual public ::userbase::view,
   virtual public filemanager::SimpleFolderListInterface
{
public:
   SimpleFolderListView (::ca::application * papp);

   simple_list_header_control    m_headerctrl;
   simple_scroll_bar             m_scrollbarVert;
   simple_scroll_bar             m_scrollbarHorz;
   FileManagerInterface *        m_pfilemanager;

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual ~SimpleFolderListView ();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   DECL_GEN_SIGNAL(_001OnLButtonDblClk)
   DECL_GEN_SIGNAL(_001OnCancelMode)
};


} // namespace filemanager
