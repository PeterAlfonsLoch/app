#pragma once


#include "SimpleFolderListInterface.h"


namespace filemanager
{


   class CLASS_DECL_ca2 SimpleFolderListView :
      virtual public ::userbase::view,
      virtual public ::filemanager::SimpleFolderListInterface
   {
   public:
      
      
      simple_list_header_control    m_headerctrl;
      sp(FileManagerInterface)        m_pfilemanager;

      
      SimpleFolderListView (sp(::ca::application) papp);
      virtual ~SimpleFolderListView ();
      
      virtual void install_message_handling(::ca::message::dispatch * pinterface);
      virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
      virtual void on_update(::view * pSender, LPARAM lHint, ::ca::object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);

      

      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnCancelMode)

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace filemanager




