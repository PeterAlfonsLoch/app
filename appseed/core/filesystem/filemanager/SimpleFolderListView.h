#pragma once


#include "SimpleFolderListInterface.h"


namespace filemanager
{


   class CLASS_DECL_CORE SimpleFolderListView :
      virtual public ::user::view,
      virtual public ::filemanager::SimpleFolderListInterface
   {
   public:
      
      
      simple_list_header_control    m_headerctrl;
      sp(FileManagerInterface)        m_pfilemanager;

      
      SimpleFolderListView (sp(base_application) papp);
      virtual ~SimpleFolderListView ();
      
      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual void OnDraw(::draw2d::graphics * pgraphics);      // overridden to draw this ::user::view
      virtual void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);

      

      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnCancelMode)

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace filemanager




