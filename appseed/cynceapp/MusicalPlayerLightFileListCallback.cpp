// MusicalPlayerLightFileListCallback.cpp: implementation of the MusicalPlayerLightFileListCallback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MusicalPlayerLightFileListCallback.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MusicalPlayerLightFileListCallback::MusicalPlayerLightFileListCallback()
{
   CDC dc;
   dc.CreateCompatibleDC(NULL);

   m_imagelistSubItemHover.Create(16, 16, 0,  10, 10);

   m_imagelistSubItemHover.Add(
      (HICON) ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_EXECUTE_PLAY),
         IMAGE_ICON,
         16,
         16,
         LR_SHARED));

   CImaging::GetImaging()->CreateHueImageList(
      &dc,
      &m_imagelistNormal,
      &m_imagelistSubItemHover,
      RGB(220, 220, 215),
      0.50);

   CImaging::GetImaging()->CreateColorBlendImageList(
      &m_imagelistItemHover,
      &m_imagelistSubItemHover,
      RGB(220, 220, 215),
      127);

}

MusicalPlayerLightFileListCallback::~MusicalPlayerLightFileListCallback()
{

}


int MusicalPlayerLightFileListCallback::GetActionButtonCount()
{
   return 1;
}

void MusicalPlayerLightFileListCallback::InitializeActionButton(int i, BaseButtonControl * pbutton)
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
      }
      break;
   }
}

void MusicalPlayerLightFileListCallback::OnButtonAction(
   int i,
   FileManagerItem & item)
{
   if(i == 0) // Play Button
   {
      MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
      if(item.m_strExtra.IsEmpty())
      {
         papp->_001OpenDocumentFile(item.m_strPath);
      }
      else
      {
         papp->_001OpenDocumentFile(item.m_strPath + ":" + item.m_strExtra);
      }
   }
}


void MusicalPlayerLightFileListCallback::OnMenuItemAction(int iId)
{
}

bool MusicalPlayerLightFileListCallback::GetMenuItemCallback(int iId)
{
   if(iId == ID_EXECUTE_PLAY)
   {
      return true;
   }
   return false;
}

void MusicalPlayerLightFileListCallback::GetMenuItemUpdate(int iId, CCmdUI * pcmdui)
{
   if(iId == ID_EXECUTE_PLAY)
   {
   }
}
