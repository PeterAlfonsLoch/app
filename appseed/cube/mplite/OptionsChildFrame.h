#pragma once
#include "MediaLibraryViewUpdateHint.h"

namespace mplite
{

   class MediaLibraryView;

   class CLASS_DECL_CA2_CUBE OptionsChildFrame :
      public simple_child_frame
   {
   public:
      OptionsChildFrame(::ca::application * papp);

      simple_toolbar           m_toolbar;
      simple_toolbar           m_toolbar1;

      MediaLibraryView * GetMainView();

      void LoadToolBar(int iToolBar, const char * pszToolBar);
      void DestroyToolBar(int iToolbar);
      EMediaLibraryView GetViewId();




      virtual ~OptionsChildFrame();

      DECL_GEN_SIGNAL(_001OnCreate)
      afx_msg void OnViewAllMedia();
      afx_msg void OnUpdateViewAllMedia(cmd_ui * pcmdui);
      afx_msg void OnViewMediaExplorer();
      afx_msg void OnUpdateViewMediaExplorer(cmd_ui * pcmdui);
      afx_msg void OnChangeEditSearch();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   };

} // namespace mplite