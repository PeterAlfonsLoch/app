#pragma once

#include "MediaLibraryViewUpdateHint.h"

namespace mplite
{

   class MediaLibraryView;

   class CLASS_DECL_CA2_CUBE MediaLibraryChildFrame :
      public simple_child_frame
   {
   public:
      MediaLibraryChildFrame(::ca::application * papp);

      simple_toolbar           m_toolbar;
      MediaLibraryView * GetMainView();
      EMediaLibraryView GetViewId();

      bool CreateBars();
      bool DestroyBars();

      virtual ~MediaLibraryChildFrame();

      afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
      afx_msg void OnViewAllMedia();
      afx_msg void OnUpdateViewAllMedia(cmd_ui * pcmdui);
      afx_msg void OnViewMediaExplorer();
      afx_msg void OnUpdateViewMediaExplorer(cmd_ui * pcmdui);
      afx_msg void OnViewVeriwellkaraokelibraryexplorer();
      afx_msg void OnUpdateViewVeriwellkaraokelibraryexplorer(cmd_ui * pcmdui);
      afx_msg void OnChangeEditSearch();
      DECL_GEN_SIGNAL(_001OnAppLanguage)
      
      void _001InitializeFormPreData(::user::form * pform);
   };

} // namespace mplite