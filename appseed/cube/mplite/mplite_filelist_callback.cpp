#include "StdAfx.h"

namespace mplite
{

   filelist_callback::filelist_callback(::ca::application * papp) :
      ca(papp),
      m_imagelistSubItemHover(papp),
      m_imagelistItemHover(papp),
      m_imagelistNormal(papp)
   {
      ::ca::graphics_sp spgraphics(get_app());
      spgraphics->CreateCompatibleDC(NULL);

      m_imagelistSubItemHover.create(16, 16, 0,  10, 10);

      m_imagelistSubItemHover.add_matter("execute_play_16.png");

/*      m_imagelistSubItemHover.add(
         (HICON) ::LoadImage(
            System.m_hInstance,
            MAKEINTRESOURCE(IDI_EXECUTE_PLAY),
            IMAGE_ICON,
            16,
            16,
            LR_SHARED));*/

      System.imaging().CreateHueImageList(
         spgraphics,
         &m_imagelistNormal,
         &m_imagelistSubItemHover,
         RGB(220, 220, 215),
         0.50);

      System.imaging().Createcolor_blend_ImageList(
         &m_imagelistItemHover,
         &m_imagelistSubItemHover,
         RGB(220, 220, 215),
         127);

   }

   filelist_callback::~filelist_callback()
   {

   }


   int filelist_callback::GetActionButtonCount()
   {
      return 1;
   }

   void filelist_callback::InitializeActionButton(id i, BaseButtonControl * pbutton)
   {
      switch(i)
      {
      case 0: // PlayButton
         {
            pbutton->m_pimagelistNormal = &m_imagelistNormal;
            pbutton->m_iImageNormal = 0;
            pbutton->m_pimagelistItemHover = &m_imagelistItemHover;
            pbutton->m_iImageItemHover = 0;
            pbutton->m_pimagelistSubItemHover = &m_imagelistSubItemHover;
            pbutton->m_iImageSubItemHover = 0;
            //pbutton->descriptor().m_iSubItem = 0;
         }
         break;
      }
   }

   void filelist_callback::OnButtonAction(id i, ::fs::item & item)
   {
      PlaylistCentral & playlistcentral = PlaylistCentralContainer::AppGetPlaylistCentral(get_app());
      PlaylistDoc * pdoc = playlistcentral.GetCurrentPlaylist(true);
      if(i == 0) // Play button
      {
         pdoc->AddSong(item.m_strPath, PlaylistDoc::AddSongAndPlay, true, true);
      }
   }


   void filelist_callback::OnMenuItemAction(id iId, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(itema);
   }

   bool filelist_callback::GetMenuItemCallback(id iId)
   {
      if(iId == "ID_EXECUTE_PLAY")
      {
         return true;
      }
      return false;
   }

   void filelist_callback::GetMenuItemUpdate(id iId, ::fs::item_array & itema, cmd_ui * pcmdui)
   {
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(pcmdui);
      if(iId == "ID_EXECUTE_PLAY")
      {
      }
   }

} // namespace mplite