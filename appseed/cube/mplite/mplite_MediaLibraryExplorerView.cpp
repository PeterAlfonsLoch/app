#include "StdAfx.h"

#include "MediaLibraryExplorerTreeView.h"
#include "MediaLibraryExplorerView.h"
#include "MediaLibraryListView.h"

namespace mplite
{

   MediaLibraryExplorerView::MediaLibraryExplorerView(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
      

   }

   MediaLibraryExplorerView::~MediaLibraryExplorerView()
   {
   }

   void MediaLibraryExplorerView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &MediaLibraryExplorerView::_001OnCreate);
   }



   void MediaLibraryExplorerView::OnDraw(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      //::userbase::document* pDoc = get_document();
      // TODO: add draw code here
   }

   /////////////////////////////////////////////////////////////////////////////
   // MediaLibraryExplorerView diagnostics

   #ifdef _DEBUG
   void MediaLibraryExplorerView::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void MediaLibraryExplorerView::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void MediaLibraryExplorerView::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
   }

   void MediaLibraryExplorerView::CreateViews()
   {
      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);
     
      set_position_rate(0, 0.2);

      

      create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(MediaLibraryExplorerTreeView);

   // trans   MediaLibraryExplorerTreeView * ptree = dynamic_cast < MediaLibraryExplorerTreeView * >
         // (pane_view::CreateView(&cc, 100, this));

      

   // trans   SetPane(0, ptree, false);

      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(MediaLibraryListView);

   // trans   MediaLibraryListView * pmediaview = 
         // dynamic_cast < MediaLibraryListView * > 
            // (pane_view::CreateView(&cc, 101, this));

      

   // trans   SetPane(1, pmediaview, false);

      layout();

   }

} // namespace mplite