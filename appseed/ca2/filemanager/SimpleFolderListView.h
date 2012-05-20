#pragma once

#include "SimpleFolderListInterface.h"


namespace filemanager
{

class CLASS_DECL_ca2 SimpleFolderListView :
   virtual public ::userbase::view,
   virtual public filemanager::SimpleFolderListInterface
{
public:
   SimpleFolderListView (::ca::application * papp);

   simple_list_header_control    m_headerctrl;
   FileManagerInterface *        m_pfilemanager;

   virtual void install_message_handling(::gen::message::dispatch * pinterface);
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual ~SimpleFolderListView ();
#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   DECL_GEN_SIGNAL(_001OnLButtonDblClk)
   DECL_GEN_SIGNAL(_001OnCancelMode)
};


} // namespace filemanager
