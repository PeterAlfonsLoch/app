#include "StdAfx.h"
#include "PlaylistView.h"


CPlaylistView::CPlaylistView(::ca::application * papp) :
   ca(papp),
   simple_list_view(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   form(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   ::user::list(papp)
{
   m_dataid = "CPlaylistView";
}

CPlaylistView::~CPlaylistView()
{
}

#ifdef _DEBUG
void CPlaylistView::assert_valid() const
{
   simple_list_view::assert_valid();
}

void CPlaylistView::dump(dump_context & dumpcontext) const
{
   simple_list_view::dump(dumpcontext);
}
#endif //_DEBUG

void CPlaylistView::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(lHint);
//   PlaylistDoc * pdoc = get_document();
   PlaylistViewUpdateHint * puh = (PlaylistViewUpdateHint *) pHint;
   if(puh != NULL)
   {
      switch(puh->GetHint())
      {
      case PlaylistViewUpdateHint::HintPop:
         {
            OnActivateFrame(WA_INACTIVE, dynamic_cast < userbase::frame_window * > (GetParentFrame()));
            (dynamic_cast < userbase::frame_window * > (GetParentFrame()))->ActivateFrame(SW_SHOW);
            OnActivateView(TRUE, this, this);
            RedrawWindow();
         }
         break;
      case PlaylistViewUpdateHint::HintInitial:
         {
            _001UpdateColumns();
         }
      }
   }
   //_001SetItemCountEx(pdoc->GetSongCount());
   _001OnUpdateItemCount();
}

PlaylistDoc * CPlaylistView::get_document()
{
   return dynamic_cast < PlaylistDoc * > (::view::get_document());
}

void CPlaylistView::_001InsertColumns()
{
   //DBCentralInterface * pDataCentral = &System.db();

   Column column;

/*   EMode emode = m_emode;

    if(emode == ModeMinimum)
    {
      column.m_iWidth = 300;
//      column.m_uiText = IDS_PLAYLIST_CODE;
      column.m_iSubItem = 0;
//      column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
      column.m_iSmallImageWidth = 16;
      column.m_crSmallMask = RGB(255, 0, 255);
      _001AddColumn(column);
    }
    else if(emode == ModeNormal)*/
    {
      column.m_iWidth = 170;
//      column.m_uiText = IDS_PLAYLIST_CODE;
      column.m_iSubItem = 2;
//      column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
      column.m_iSmallImageWidth = 16;
      column.m_crSmallMask = RGB(255, 0, 255);
      _001AddColumn(column);

//      column.m_uiText = IDS_PLAYLIST_SONG_NAME;
      column.m_iWidth = 400;
      column.m_iSubItem = 3;
      _001AddColumn(column);

    }

}
