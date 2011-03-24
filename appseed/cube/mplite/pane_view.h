#pragma once

#include "pane_view_update_hint.h"

class ::userbase::single_document_template;
class view;
class create_context;

namespace mplite
{

   class CLASS_DECL_CA2_CUBE pane_view : 
      public ::userex::pane_tab_view
   {
   public:
      
      
      ::userbase::single_document_template * m_pdoctemplateAlbum;
      ::userbase::single_document_template * m_pdoctemplateOptions;
      ::userbase::single_document_template * m_pdoctemplateAudioControl;

      
      pane_view(::ca::application * papp);
      virtual ~pane_view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      

      void rotate();

      ::user::interaction* GetKaraokeWindow();
      document * GetMediaLibraryDoc();
      void on_create_view(view_data * pviewdata);
      void on_show_view();

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
   };

} // namespace mplite